#pragma once
#include <memory>
#include "Weapon.h"

class SpriteWrapper;

class Grapple : public Weapon
{
public:

	Grapple(IWeaponHolder* aWeaponHolder);
	virtual ~Grapple() override;

	virtual void Init();
	virtual void Update(float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	virtual bool Shoot() override;

protected:

	virtual void LoadJson(const JsonData& someJsonData) override;
	virtual void Setup() override;

private:
	// Variables moved to GrapplingHookProjectile
	//float myMaxDistance{};
	//float myHookSpeed{};
	//float myContractSpeed{};
};
