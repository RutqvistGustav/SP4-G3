#pragma once

#include "Weapon.h"

class Shotgun : public Weapon
{
public:

	Shotgun(IWeaponHolder* aWeaponHolder);
	virtual ~Shotgun() override;

	virtual void Update(float aDeltaTime, UpdateContext& anUpdateContext, const CU::Vector2<float>& aPlayerPosition) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	virtual void Shoot(const CU::Vector2<float> aPlayerPosition) override;

	virtual void Reload();

protected:

	virtual void LoadJson(const JsonData& someJsonData) override;
	virtual void Setup() override;

	void SetLoadedAmmo(int anAmount);

	bool IsReloadingComplete() const;
	bool IsReloading() const;
	bool IsLoaded() const;

private:

	int myLoadedAmmo{};

	float myTime{};

	float myNextFireTime{};
	float myReloadCompleteTime{ -1.0f };

	// Loaded from JSON
	int myAmmoPerClip{};

	float myReloadDuration{};

	float myDamage{};

	float myAoeAngle{};
	float myAoeLength{};

	float myRecoilKnockbackStrength{};

};
