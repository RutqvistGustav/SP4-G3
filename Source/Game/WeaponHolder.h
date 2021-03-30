#pragma once

class Weapon;
class PowerUpType;

class IWeaponHolder
{
public:

	virtual void ApplyRecoilKnockback(Weapon* aWeapon, float someStrength, bool aShootDown = false) = 0;
	virtual void ActivatePowerUp(PowerUpType* aPowerUpType) = 0;
};
