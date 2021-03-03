#pragma once
#include "Weapon.h"
class Shotgun : public Weapon
{
public:
	Shotgun(const float aRangeValue);
	~Shotgun();

	void Shoot() override;

private:
};

