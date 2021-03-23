#pragma once

#include "Weapon.h"

#include <memory>

class SpriteWrapper;
class GrappleHookProjectile;
class Scene;

class Grapple : public Weapon
{
public:

	Grapple(Scene* aScene, IWeaponHolder* aWeaponHolder);
	virtual ~Grapple() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	virtual void Shoot() override;

	const bool& IsLoaded() const;
	void Reload(const float aDeltaTime);

	GrappleHookProjectile* GetProjectile();

protected:

	virtual void LoadJson(const JsonData& someJsonData) override;
	virtual void Setup() override;

private:

	bool myIsLoaded = true;

	float myMaxDistance{};
	float myCoolDown{};
	float myCoolDownReset{};

	std::unique_ptr<GrappleHookProjectile> myProjectile;

};
