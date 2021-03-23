#pragma once

#include "Vector2.hpp"

#include "WeaponHolder.h"
#include "JsonData.h"

class JsonManager;
struct UpdateContext;
struct RenderContext;
class RenderQueue;

class Player;

class Scene;

class Weapon;
class WeaponFactory;
class Grapple;

class PlayerWeaponController : protected IWeaponHolder
{
public:

	PlayerWeaponController(Scene* aScene, Player* aPlayer);
	~PlayerWeaponController();

	void Init();

	void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);
	
	virtual void StopGrappling();

protected:

	CU::Vector2<float> ComputeAimDirection(UpdateContext& anUpdateContext);

	virtual void ApplyRecoilKnockback(Weapon* aWeapon, float someStrength) override;
	virtual void OnGrappleHit(/*GameObjectType , */ const CU::Vector2<float>& aTargetPosition, const CU::Vector2<float>& aGrapplingDirection) override;
private:

	Scene* myScene;
	Player* myPlayer;

	std::shared_ptr<Grapple> myGrapple;
	std::shared_ptr<Weapon> myShotgun;

};
