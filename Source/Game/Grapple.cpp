#include "stdafx.h"
#include "Grapple.h"
#include "GrappleHookProjectile.h"

#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "JsonManager.h"

// TODO - Instatiate Hook towards nearest Grapple object
//		- Pull Player in Hook direction
//		- Cancel Hook midair for some momentum
//		- Independant cooldown on the two charges

Grapple::Grapple(IWeaponHolder* aWeaponHolder) :
	Weapon(WeaponType::Grapple, aWeaponHolder)
{
}

Grapple::~Grapple() = default;

void Grapple::InitGameObjects(Scene* aScene)
{
	myProjectile = std::make_unique<GrappleHookProjectile>(aScene, GetWeaponHolder());
	myProjectile->SetVariables(myMaxDistance, myHookSpeed, myContractSpeed);
	//myProjectile->Init(aScene->GetGlobalServiceProvider()->GetJsonManager()->GetData(""));
}

void Grapple::Update(float aDeltaTime, UpdateContext& anUpdateContext, const CU::Vector2<float>& aPlayerPosition)
{
	myProjectile->Update(aDeltaTime, aPlayerPosition);
}

void Grapple::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	myProjectile->Render(aRenderQueue, aRenderContext);
}

void Grapple::Shoot(const CU::Vector2<float> aPlayerPosition)
{
	myProjectile->SetPosition(aPlayerPosition);
	myProjectile->SpawnProjectile(GetDirection());
}

void Grapple::LoadJson(const JsonData& someJsonData) // variables moved to GrappleHookProjectile
{
	myMaxDistance = someJsonData["maxDistance"];
	myHookSpeed = someJsonData["hookSpeed"];
	myContractSpeed = someJsonData["contractSpeed"];
}

void Grapple::Setup()
{
}
