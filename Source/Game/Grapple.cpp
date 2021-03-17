#include "stdafx.h"
#include "Grapple.h"
#include "GrappleHookProjectile.h"

#include "Scene.h"

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
	//Scene* scene = nullptr; // temp
	//myProjectile = std::make_unique<GrappleHookProjectile>(scene); // needs scene
}

void Grapple::Update(float aDeltaTime, UpdateContext& anUpdateContext, const CU::Vector2<float>& aPlayerPosition)
{
	//myProjectile->Update(aDeltaTime, aPlayerPosition);
}

void Grapple::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
{
}

void Grapple::Shoot()
{
	myProjectile->SpawnProjectile(GetDirection());
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
