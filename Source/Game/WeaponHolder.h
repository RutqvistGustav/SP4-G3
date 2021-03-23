#pragma once

class Weapon;

class IWeaponHolder
{
public:

	virtual void ApplyRecoilKnockback(Weapon* aWeapon, float someStrength) = 0;
	virtual void OnGrappleHit(/*GameObjectType , */ const CU::Vector2<float>& aTargetPosition, const CU::Vector2<float>& aDirection) = 0;
	virtual void StopGrappling() = 0;
};
