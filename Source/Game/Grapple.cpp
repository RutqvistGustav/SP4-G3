#include "stdafx.h"
#include "Grapple.h"

// TODO - Instatiate Hook towards nearest Grapple object
//		- Pull Player in Hook direction
//		- Cancel Hook midair for some momentum
//		- Independant cooldown on the two charges
//		- Add JsonValues!!!!!

Grapple::Grapple(const float aRangeValue) : 
	Weapon(eWeaponType::Grapple, aRangeValue)
{}

Grapple::~Grapple()
{
}

void Grapple::Shoot()
{
}
