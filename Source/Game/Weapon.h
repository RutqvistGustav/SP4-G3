#pragma once

#include "GameObject.h"

#include "Vector2.hpp"

#include "WeaponType.h"
#include "JsonData.h"
#include "PowerUpType.h"

struct UpdateContext;
struct RenderContext;
class JsonManager;
class RenderQueue;
class IWeaponHolder;

class Weapon : public GameObject
{
public:

	Weapon(const WeaponType aWeaponType, Scene* aScene, IWeaponHolder* aWeaponHolder);
	virtual ~Weapon() = 0;

	virtual void Init(const JsonData& someJsonData);

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) = 0;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) = 0;
	virtual void ActivatePowerUp(PowerUpType aPowerUpType);

	virtual void Shoot() = 0;
	virtual void Boost() = 0;

	inline void SetDirection(const CU::Vector2<float>& aDirection) { myDirection = aDirection; }
	inline const CU::Vector2<float>& GetDirection() const { return myDirection; }

	inline const WeaponType GetWeaponType() const { return myWeaponType; }

protected:

	using GameObject::Init;

	virtual void LoadJson(const JsonData& someJsonData) = 0;
	virtual void Setup() = 0;

	inline IWeaponHolder* GetWeaponHolder() { return myWeaponHolder; }

private:

	CU::Vector2<float> myDirection{ 1.0f, 0.0f };

	IWeaponHolder* myWeaponHolder{};
	WeaponType myWeaponType;

};
