#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(const eWeaponType aWeaponType, const float aRangeValue) :
	myRange(aRangeValue),
	myWeaponType(aWeaponType)
{}

Weapon::~Weapon()
{
}

const eWeaponType Weapon::GetWeaponType()
{
	return myWeaponType;
}

