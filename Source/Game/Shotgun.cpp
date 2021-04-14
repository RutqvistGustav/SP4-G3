#include "stdafx.h"
#include "Shotgun.h"
#include "GlobalServiceProvider.h"
#include "AudioManager.h"

#include "Collider.h"
#include "CollisionManager.h"
#include "CollisionInfo.h"

#include "Enemy.h"

#include "GlobalServiceProvider.h"
#include "GameMessenger.h"
#include "SpawnParticleEffectMessage.h"

#include "WeaponHolder.h"

#include "MathHelper.h"

#include "Scene.h"

Shotgun::Shotgun(Scene* aScene, IWeaponHolder* aWeaponHolder)
	: Weapon(WeaponType::Shotgun, aScene, aWeaponHolder)
{
	myShotVolume = std::make_shared<Collider>(myPosition, CU::Vector2<float>(0.0f, 0.0f));
	myShotVolume->SetCollisionListener(this);
	myShotVolume->SetGameObject(this);

#ifdef _DEBUG

	myShotVolume->myDoRender = false;

#endif // _DEBUG
}

Shotgun::~Shotgun()
{
	myScene->GetCollisionManager()->RemoveCollider(myShotVolume);
}

void Shotgun::Update(const float aDeltaTime, UpdateContext& /*anUpdateContext*/)
{
	myTime += aDeltaTime;

	if (myIsShotVolumeActive)
	{
		myIsShotVolumeActive = false;
	}
	else
	{
		myShotVolume->SetBoxSize({ myAoeLength, min(myAoeLength, 125.0f) });
		myShotVolume->SetPosition(GetPosition() + GetDirection() * myShotVolume->GetBoxSize().x * 0.5f);
	}

	if (IsReloadingComplete())
	{
		SetLoadedAmmo(myAmmoPerClip);
		myReloadCompleteTime = -1.0f;
		GetScene()->GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Weapon/Reload.mp3");
		Notify(myLoadedAmmo);
	}

	UpdatePowerUps(aDeltaTime);
}

void Shotgun::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
{
	// TODO: Render weapon?
}

void Shotgun::ActivatePowerUp(PowerUpType aPowerUpType)
{
	myIsPowerUpActive = true;
	myActivePowerUp = aPowerUpType;
	if (myActivePowerUp == PowerUpType::Berserk)
	{
		myPowerUpDuration = myBerserkDuration;
		myPowerUpDamage = myBerserkDamage;
		myPowerUpReloadDuration = myBerserkReloadDuration;
	}
}

void Shotgun::UpdatePowerUps(const float aDeltaTime)
{
	if (myIsPowerUpActive == true)
	{
		myPowerUpDuration -= aDeltaTime;
		if (myPowerUpDuration <= 0)
		{
			if (myActivePowerUp == PowerUpType::Berserk)
			{
				GetWeaponHolder()->DisablePowerUp();
			}
			myIsPowerUpActive = false;
		}
	}
}

void Shotgun::Shoot()
{
	if (!IsLoaded())
	{
		return;
	}

	GetScene()->GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Weapon/shotgun-firing-1.wav");

	// TODO: Could implement with an immediate overlap test but for now we need to do this since that is not implemented
	myIsShotVolumeActive = true;

	GetWeaponHolder()->ApplyRecoilKnockback(this, myRecoilKnockbackStrength);

	SetLoadedAmmo(myLoadedAmmo - 1);

	SpawnMuzzleFlash();

	Notify(myLoadedAmmo);

	if (!IsLoaded())
	{
		Reload();
	}
}

void Shotgun::Boost()
{
	if (!IsLoaded())
	{
		return;
	}
	GetScene()->GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Weapon/shotgun-firing-3.wav");

	// TODO: Could implement with an immediate overlap test but for now we need to do this since that is not implemented
	myIsShotVolumeActive = true;

	// NOTE: For boosting we'll modify the shape and position of the shot volume to point more down
	myShotVolume->SetBoxSize({ min(myAoeLength, 125.0f), myAoeLength });
	myShotVolume->SetPosition(GetPosition() + CU::Vector2<float>(0.0f, 1.0f) * myShotVolume->GetBoxSize().y * 0.5f);

	GetWeaponHolder()->ApplyRecoilKnockback(this, myBoostKnockBackStrength, true);

	SetLoadedAmmo(myLoadedAmmo - 1);

	Notify(myLoadedAmmo);

	if (!IsLoaded())
	{
		Reload();
	}
}

void Shotgun::Reload()
{
	if (!IsReloading())
	{
		if (myIsPowerUpActive == false)
		{
			myReloadCompleteTime = myTime + myReloadDuration;
		}
		else
		{
			myReloadCompleteTime = myTime + myPowerUpReloadDuration;
		}
	}
}

void Shotgun::LoadJson(const JsonData& someJsonData)
{
	myAmmoPerClip = someJsonData["ammoPerClip"];

	myReloadDuration = someJsonData["reloadDuration"];

	myDamage = someJsonData["damage"];

	myAoeAngle = someJsonData["aoeAngle"];
	myAoeLength = someJsonData["aoeLength"];

	myRecoilKnockbackStrength = someJsonData["recoilKnockbackStrength"];
	myBoostKnockBackStrength = someJsonData["boostKnockbackStrength"];

	myBerserkDuration = someJsonData["Berserk"].at("Duration");
	myBerserkDamage = someJsonData["Berserk"].at("Damage");
	myBerserkReloadDuration = someJsonData["Berserk"].at("ReloadDuration");
}

void Shotgun::Setup()
{
	SetLoadedAmmo(myAmmoPerClip);

	myShotVolume->SetBoxSize({ myAoeLength, min(myAoeLength, 125.0f) });

	myScene->GetCollisionManager()->AddCollider(myShotVolume);
}

void Shotgun::SetLoadedAmmo(int anAmount)
{
	if (anAmount >= 0 && myLoadedAmmo <= myAmmoPerClip)
	{
		myLoadedAmmo = anAmount;
	}
}

bool Shotgun::IsReloadingComplete() const
{
	return myReloadCompleteTime >= 0.0f && myTime >= myReloadCompleteTime;
}

bool Shotgun::IsReloading() const
{
	return myReloadCompleteTime >= 0.0f && myTime < myReloadCompleteTime;
}

bool Shotgun::IsLoaded() const
{
	return myLoadedAmmo > 0;
}

void Shotgun::SpawnMuzzleFlash() const
{
	SpawnParticleEffectMessageData spawnData;
	spawnData.myType = ParticleEffectType::MuzzleFlash;
	spawnData.myPosition = GetPosition() + GetDirection() * 4.0f * 0.5f * 75.0f;
	spawnData.myRotation = std::atan2f(GetDirection().y, GetDirection().x);
	spawnData.myScale = 1.0f;

	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Send(GameMessage::SpawnParticleEffect, &spawnData);
}

void Shotgun::CheckCollisionHit(const CollisionInfo& someCollisionInfo)
{
	if (!myIsShotVolumeActive)
		return;

	GameObject* gameObject = someCollisionInfo.myOtherCollider->GetGameObject();

	if (gameObject != nullptr && gameObject->GetTag() == GameObjectTag::Enemy)
	{
		CU::Vector2<float> toEnemy = gameObject->GetPosition() - GetPosition();

		Enemy* enemy = static_cast<Enemy*>(gameObject);

		toEnemy.Normalize();
		toEnemy.y = 0.0f; // NOTE: No vertical movements from getting shot

		enemy->ApplyForce(toEnemy * myRecoilKnockbackStrength);
		enemy->TakeDamage(myDamage);
	}
}

void Shotgun::OnEnter(const CollisionInfo& someCollisionInfo)
{
	CheckCollisionHit(someCollisionInfo);
}

void Shotgun::OnStay(const CollisionInfo& someCollisionInfo)
{
	CheckCollisionHit(someCollisionInfo);
}
