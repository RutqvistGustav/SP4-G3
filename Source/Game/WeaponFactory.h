#pragma once

#include "BehaviourFactoryBase.h"

#include <string>

class IWeaponHolder;
class JsonManager;
class Weapon;

class WeaponFactory : public BehaviourFactoryBase<std::string, Weapon, std::string, std::string, IWeaponHolder*>
{
public:

	WeaponFactory(const JsonManager* aJsonManager);
	virtual ~WeaponFactory() override;

	std::shared_ptr<Weapon> CreateWeapon(const std::string& aKey, IWeaponHolder* aWeaponHolder) const;

protected:

	virtual std::shared_ptr<Weapon> ConstructType(std::shared_ptr<Weapon> aBehaviour, const std::string& someTypeData) const override;

private:

	const JsonManager* myJsonManager;

};
