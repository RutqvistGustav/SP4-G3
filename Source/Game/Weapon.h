#pragma once
enum class eWeaponType
{
	Shotgun,
	Grapple
};

class Weapon
{
public:
	Weapon(const eWeaponType aWeaponType, const float aRangeValue);
	~Weapon();

	virtual void Shoot() {};
	
	const eWeaponType GetWeaponType();

protected:
	float myRange;

	eWeaponType myWeaponType;
};

