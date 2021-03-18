#include "stdafx.h"
#include "Shotgun.h"

#include "Collider.h"
#include "CollisionManager.h"

#include "Enemy.h"

#include "WeaponHolder.h"

#include "MathHelper.h"

// TODO: DEBUG: REMOVE
#include <iostream>

Shotgun::Shotgun(Scene* aScene, IWeaponHolder* aWeaponHolder)
	: Weapon(WeaponType::Shotgun, myScene, aWeaponHolder)
{
	myShotVolume = std::make_shared<Collider>(this, myPosition);
}

Shotgun::~Shotgun()
{
	CollisionManager::GetInstance()->RemoveCollider(myShotVolume);
}

void Shotgun::Update(float aDeltaTime, UpdateContext& /*anUpdateContext*/)
{
	myTime += aDeltaTime;

	if (myIsShotVolumeActive)
	{
		myIsShotVolumeActive = false;
	}
	else
	{
		myShotVolume->SetPos(GetPosition() + GetDirection() * myShotVolume->GetRadius() * 0.5f);
	}

	if (IsReloadingComplete())
	{
		SetLoadedAmmo(myAmmoPerClip);
		myReloadCompleteTime = -1.0f;
	}
}

void Shotgun::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
{
	// TODO: Render weapon?
}

void Shotgun::Shoot()
{
	if (!IsLoaded())
	{
		return;
	}

	// TODO: Could implement with an immediate overlap test but for now we need to do this since that is not implemented
	myIsShotVolumeActive = true;

	GetWeaponHolder()->ApplyRecoilKnockback(this, myRecoilKnockbackStrength);

	SetLoadedAmmo(myLoadedAmmo - 1);

	if (!IsLoaded())
	{
		Reload();
	}
}

void Shotgun::Reload()
{
	if (!IsReloading())
	{
		myReloadCompleteTime = myTime + myReloadDuration;
	}
}

void Shotgun::OnCollision(GameObject* aGameObject)
{
	if (!myIsShotVolumeActive)
		return;

	if (aGameObject->GetTag() == GameObjectTag::Enemy)
	{
		const CU::Vector2<float> toEnemy = aGameObject->GetPosition() - GetPosition();
		const float degDiff = MathHelper::radToDeg(std::fabsf(std::atan2f(toEnemy.y, toEnemy.x) - std::atan2f(GetDirection().y, GetDirection().x)));

		if (degDiff <= myAoeAngle)
		{
			Enemy* enemy = static_cast<Enemy*>(aGameObject);
			// TODO: Damage enemy

			std::cout << "Damage enemy!" << std::endl;
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
}

void Shotgun::Setup()
{
	SetLoadedAmmo(myAmmoPerClip);

	myShotVolume->SetRadius(myAoeLength);

	CollisionManager::GetInstance()->AddCollider(myShotVolume);
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
