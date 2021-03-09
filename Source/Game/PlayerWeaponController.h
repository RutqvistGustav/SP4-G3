#pragma once

#include "WeaponHolder.h"

struct UpdateContext;
struct RenderContext;
class RenderQueue;

class Player;

class Weapon;
class WeaponFactory;

class PlayerWeaponController : protected IWeaponHolder
{
public:

	PlayerWeaponController(const WeaponFactory* aWeaponFactory, Player* aPlayer);
	~PlayerWeaponController();

	void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

protected:

	virtual void ApplyRecoilKnockback(Weapon* aWeapon, float someStrength) override;

private:

	Player* myPlayer;

	std::shared_ptr<Weapon> myGrapple;
	std::shared_ptr<Weapon> myShotgun;

};
