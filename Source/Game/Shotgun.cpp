#include "stdafx.h"
#include "Shotgun.h"

#include "Collider.h"
#include "CollisionManager.h"

#include "Enemy.h"

#include "WeaponHolder.h"

#include "MathHelper.h"

#include "Scene.h"

Shotgun::Shotgun(Scene* aScene, IWeaponHolder* aWeaponHolder)
	: Weapon(WeaponType::Shotgun, aScene, aWeaponHolder)
{
	myShotVolume = std::make_shared<Collider>(this, myPosition);
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

void Shotgun::Boost()
{
	if (!IsLoaded())
	{
		return;
	}

	// TODO: Could implement with an immediate overlap test but for now we need to do this since that is not implemented
	myIsShotVolumeActive = true;

	GetWeaponHolder()->ApplyRecoilKnockback(this, myRecoilKnockbackStrength, true);

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
		float enemyAngle = std::atan2f(toEnemy.y, toEnemy.x);
		float myAngle = std::atan2f(GetDirection().y, GetDirection().x);

		if (enemyAngle < 0.0f) enemyAngle += MathHelper::locPif * 2.0f;
		if (myAngle < 0.0f) myAngle += MathHelper::locPif * 2.0f;

		const float degDiff = MathHelper::RadToDeg(std::fabsf(enemyAngle - myAngle));

		if (degDiff <= myAoeAngle)
		{
			Enemy* enemy = static_cast<Enemy*>(aGameObject);

			enemy->ApplyForce(toEnemy.GetNormalized() * myRecoilKnockbackStrength);
			enemy->TakeDamage(myDamage);
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
}

void Shotgun::Setup()
{
	SetLoadedAmmo(myAmmoPerClip);

	myShotVolume->SetRadius(myAoeLength);

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
