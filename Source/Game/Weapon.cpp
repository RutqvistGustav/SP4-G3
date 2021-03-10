#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(const WeaponType aWeaponType, IWeaponHolder* aWeaponHolder)
	: myWeaponType(aWeaponType),
	myWeaponHolder(aWeaponHolder)
{}

Weapon::~Weapon() = default;

void Weapon::Init(const JsonData & someJsonData)
{
	LoadJson(someJsonData);
	Setup();
}
