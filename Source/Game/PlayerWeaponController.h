#pragma once

#include "Vector2.hpp"

#include "WeaponHolder.h"
#include "JsonData.h"
#include "PowerUpType.h"

class JsonManager;
struct UpdateContext;
struct RenderContext;
class RenderQueue;

class Player;

class Scene;

class Weapon;
class WeaponFactory;
class Grapple;
class Shotgun;

class PlayerWeaponController : protected IWeaponHolder
{
public:

	PlayerWeaponController(Scene* aScene, Player* aPlayer);
	~PlayerWeaponController();

	void Init();

	void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);
	virtual void ActivatePowerUp(PowerUpType aPowerUpType) override;
	virtual void DisablePowerUp() override;

	void DeactivatePowerUp();

	Shotgun* GetShotgun();

protected:

	CU::Vector2<float> ComputeWeaponPosition();
	CU::Vector2<float> ComputeAimDirection(UpdateContext& anUpdateContext);

	virtual void ApplyRecoilKnockback(Weapon* aWeapon, float someStrength, bool aShootDown = false) override;

private:

	Scene* myScene;
	Player* myPlayer;

	CU::Vector2<float> myPreviousDirection;
	std::shared_ptr<Weapon> myShotgun;

};
