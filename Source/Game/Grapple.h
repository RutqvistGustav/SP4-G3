#pragma once

#include "Weapon.h"

class Grapple : public Weapon
{
public:

	Grapple(IWeaponHolder* aWeaponHolder);
	virtual ~Grapple() override;

	virtual void Update(float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	virtual bool Shoot() override;

protected:

	virtual void LoadJson(const JsonData& someJsonData) override;
	virtual void Setup() override;

private:

	float myMaxDistance{};
	float myHookSpeed{};
	float myContractSpeed{};

};
