#include "stdafx.h"
#include "Grapple.h"

// TODO - Instatiate Hook towards nearest Grapple object
//		- Pull Player in Hook direction
//		- Cancel Hook midair for some momentum
//		- Independant cooldown on the two charges

Grapple::Grapple(IWeaponHolder* aWeaponHolder) :
	Weapon(WeaponType::Grapple, aWeaponHolder)
{}

Grapple::~Grapple() = default;

void Grapple::Init()
{
}

void Grapple::Update(float /*aDeltaTime*/, UpdateContext & /*anUpdateContext*/)
{
	// myProjectile.Update(vector2 aPlayerPosition);
}

void Grapple::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
{
}

bool Grapple::Shoot()
{
	// Spawn projectile, Insert shoot direction.
	return false;
}

void Grapple::LoadJson(const JsonData& someJsonData)
{
	//myMaxDistance = someJsonData["maxDistance"];
	//myHookSpeed = someJsonData["hookSpeed"];
	//myContractSpeed = someJsonData["contractSpeed"];

}

void Grapple::Setup()
{
}
