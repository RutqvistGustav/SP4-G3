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
	myFireTimer -= aDeltaTime;
}

void Shotgun::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
{
	// TODO: Render weapon?
}

bool Shotgun::Shoot()
{
	if (myFireTimer > 0.0f || myLoadedAmmo <= 0)
	{
		return false;
	}

	// TODO: Shoot actual bullet or do a shapecast?

	GetWeaponHolder()->ApplyRecoilKnockback(myRecoilKnockbackStrength);

	SetLoadedAmmo(myLoadedAmmo - 1);
	myFireTimer = myFireInterval;

	return true;
}

void Shotgun::Reload()
{
	if (myClipCount <= 0)
	{
		return;
	}

	SetLoadedAmmo(myAmmoPerClip);
	SetClipCount(myClipCount - 1);
}

void Shotgun::LoadJson(const JsonData& someJsonData)
{
	myMaxClipCount = someJsonData["maxClipCount"];
	myAmmoPerClip = someJsonData["ammoPerClip"];

	myFireInterval = someJsonData["fireInterval"];

	myDamage = someJsonData["damage"];

	myAoeAngle = someJsonData["aoeAngle"];
	myAoeLength = someJsonData["aoeLength"];

	myRecoilKnockbackStrength = someJsonData["recoilKnockbackStrength"];
}

void Shotgun::Setup()
{
	SetLoadedAmmo(myAmmoPerClip);
	SetClipCount(myMaxClipCount);
}

void Shotgun::SetLoadedAmmo(int anAmount)
{
	if (anAmount >= 0 && myLoadedAmmo <= myAmmoPerClip)
	{
		myLoadedAmmo = anAmount;
	}
}

void Shotgun::SetClipCount(int anAmount)
{
	if (myClipCount >= 0 && myClipCount <= myMaxClipCount)
	{
		myClipCount = anAmount;
	}
}
