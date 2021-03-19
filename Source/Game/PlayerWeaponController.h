#pragma once

#include "Vector2.hpp"

#include "WeaponHolder.h"
#include "JsonData.h"

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

	void Init(const JsonData& someJsonData);
	void Update(const float aDeltaTime, UpdateContext& anUpdateContext, const CU::Vector2<float>& aPlayerPosition);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

protected:

	CU::Vector2<float> ComputeAimDirection(UpdateContext& anUpdateContext);

	virtual void ApplyRecoilKnockback(Weapon* aWeapon, float someStrength) override;

private:

	Player* myPlayer;

	std::shared_ptr<Weapon> myGrapple;
	std::shared_ptr<Weapon> myShotgun;

};
