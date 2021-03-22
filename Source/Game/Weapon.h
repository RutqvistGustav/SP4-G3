#pragma once

#include "Vector2.hpp"

#include "WeaponType.h"
#include "JsonData.h"

struct UpdateContext;
struct RenderContext;
class JsonManager;
class RenderQueue;
class IWeaponHolder;

class JsonManager;
class Scene;

class Weapon
{
public:

	Weapon(const WeaponType aWeaponType, IWeaponHolder* aWeaponHolder);
	virtual ~Weapon() = 0;

	virtual void Init(const JsonData& someJsonData);

	virtual void InitGameObjects(Scene* aScene);

	virtual void Update(float aDeltaTime, UpdateContext& anUpdateContext, const CU::Vector2<float>& aPlayerPosition) = 0;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) = 0;

	virtual void Shoot(const CU::Vector2<float> aPlayerPosition) = 0;

	inline void SetDirection(const CU::Vector2<float>& aDirection) { myDirection = aDirection; }
	inline const CU::Vector2<float>& GetDirection() const { return myDirection; }

	inline const WeaponType GetWeaponType() const { return myWeaponType; }

protected:

	virtual void LoadJson(const JsonData& someJsonData) = 0;
	virtual void Setup() = 0;

	inline IWeaponHolder* GetWeaponHolder() { return myWeaponHolder; }

private:

	CU::Vector2<float> myDirection{ 1.0f, 0.0f };

	IWeaponHolder* myWeaponHolder{};
	WeaponType myWeaponType;

};
