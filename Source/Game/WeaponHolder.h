#pragma once

class Weapon;

class IWeaponHolder
{
public:

	virtual void ApplyRecoilKnockback(Weapon* aWeapon, float someStrength, bool aShootDown = false) = 0;

};
