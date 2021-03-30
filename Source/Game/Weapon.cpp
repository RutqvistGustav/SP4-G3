#include "stdafx.h"
#include "Weapon.h"

Weapon::Weapon(const WeaponType aWeaponType, Scene* aScene, IWeaponHolder* aWeaponHolder) :
	GameObject(aScene),
	myWeaponType(aWeaponType),
	myWeaponHolder(aWeaponHolder)
{}

Weapon::~Weapon() = default;

void Weapon::Init(const JsonData& someJsonData)
{
	Init();

	// NOTE: TODO: Ugly hack for now
	myScene->GetCollisionManager()->RemoveCollider(myCollider);
	myCollider.reset();

	LoadJson(someJsonData);
	Setup();
}
