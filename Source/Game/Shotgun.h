#pragma once

#include "Weapon.h"

class Shotgun : public Weapon
{
public:

	Shotgun(IWeaponHolder* aWeaponHolder);
	virtual ~Shotgun() override;

	virtual void Update(float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	virtual bool Shoot() override;

	virtual void Reload();

protected:

	virtual void LoadJson(const JsonData& someJsonData) override;
	virtual void Setup() override;

	void SetLoadedAmmo(int anAmount);
	void SetClipCount(int anAmount);

private:

	int myLoadedAmmo{};
	int myClipCount{};

	float myFireTimer{};

	// Loaded from JSON
	int myMaxClipCount{};
	int myAmmoPerClip{};

	float myFireInterval{};

	float myDamage{};

	float myAoeAngle{};
	float myAoeLength{};

	float myRecoilKnockbackStrength{};

};
