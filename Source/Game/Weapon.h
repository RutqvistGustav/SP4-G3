#pragma once

#include "WeaponType.h"
#include "JsonData.h"

struct UpdateContext;
struct RenderContext;
class JsonManager;
class RenderQueue;
class IWeaponHolder;

class Weapon
{
public:

	Weapon(const WeaponType aWeaponType, IWeaponHolder* aWeaponHolder);
	virtual ~Weapon() = 0;

	virtual void Init(const JsonData& someJsonData);

	virtual void Update(float aDeltaTime, UpdateContext& anUpdateContext) = 0;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) = 0;

	virtual bool Shoot() = 0;

	inline const WeaponType GetWeaponType() const { return myWeaponType; }

protected:

	virtual void LoadJson(const JsonData& someJsonData) = 0;
	virtual void Setup() = 0;

	inline IWeaponHolder* GetWeaponHolder() { return myWeaponHolder; }

private:

	IWeaponHolder* myWeaponHolder{};
	WeaponType myWeaponType;

};
