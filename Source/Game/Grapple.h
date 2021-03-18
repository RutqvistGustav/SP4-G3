#pragma once
#include <memory>
#include "Weapon.h"

class SpriteWrapper;
class GrappleHookProjectile;

class Grapple : public Weapon
{
public:

	Grapple(Scene* aScene, IWeaponHolder* aWeaponHolder);
	virtual ~Grapple() override;

	virtual void Init();
	virtual void Update(float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	virtual void Shoot() override;

protected:

	virtual void LoadJson(const JsonData& someJsonData) override;
	virtual void Setup() override;

private:
	std::unique_ptr<GrappleHookProjectile> myProjectile;

	//float myMaxDistance{};
	//float myHookSpeed{};
	//float myContractSpeed{};
};
