#pragma once
#include "Weapon.h"
class Grapple : public Weapon
{
public:
	Grapple(const float aRangeValue);
	~Grapple();

	void Shoot() override;

private:
	//Example Variables taken from GDD
	//float myLaunchSpeed;
	//float myPullSpeed;
	//float myPassThroughSpeed;
};
