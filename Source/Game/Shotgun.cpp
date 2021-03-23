#include "stdafx.h"
#include "Shotgun.h"

#include "WeaponHolder.h"

// TODO - Instatiate Shotgun AoE

Shotgun::Shotgun(IWeaponHolder* aWeaponHolder)
	: Weapon(WeaponType::Shotgun, aWeaponHolder)
{}

Shotgun::~Shotgun() = default;

void Shotgun::Update(float aDeltaTime, UpdateContext& /*anUpdateContext*/)
{
	myTime += aDeltaTime;

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

void Shotgun::Shoot(const CU::Vector2<float> aPlayerPosition)
{
	if (!IsLoaded())
	{
		return false;
	}

	// TODO: Shoot actual bullet or do a shapecast?

	GetWeaponHolder()->ApplyRecoilKnockback(this, myRecoilKnockbackStrength);

	SetLoadedAmmo(myLoadedAmmo - 1);

	if (!IsLoaded())
	{
		Reload();
	}

	return true;
}

void Shotgun::Reload()
{
	if (!IsReloading())
	{
		myReloadCompleteTime = myTime + myReloadDuration;
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
