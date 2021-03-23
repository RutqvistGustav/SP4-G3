#include "stdafx.h"
#include "Grapple.h"
#include "GrappleHookProjectile.h"

#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "JsonManager.h"
#include "Ray.hpp"

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
	myProjectile->Init(aScene->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/Weapons.json")["grapple"]);
	//myRay.InitWith2Points(CU::Vector2<float>(), );
}

void Grapple::Update(float aDeltaTime, UpdateContext& anUpdateContext, const CU::Vector2<float>& aPlayerPosition)
{
	myProjectile->Update(aDeltaTime, aPlayerPosition);
	Reload(aDeltaTime);
}

void Grapple::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	myProjectile->Render(aRenderQueue, aRenderContext);
}

void Grapple::UpdateRay(const float aDeltaTime)
{
}

void Grapple::Shoot(const CU::Vector2<float> aPlayerPosition)
{
	if (!myIsLoaded) return;

	myProjectile->SetPosition(aPlayerPosition);
	myProjectile->SpawnProjectile(GetDirection());
	myIsLoaded = false;
}

const bool& Grapple::IsLoaded() const
{
	return myIsLoaded;
}

void Grapple::Reload(const float aDeltaTime)
{
	if (!myIsLoaded)
	{
		myCoolDown -= aDeltaTime;
		if (myCoolDown <= 0)
		{
			myIsLoaded = true;
			myCoolDown = myCoolDownReset;
		}
	}
}

GrappleHookProjectile* Grapple::GetProjectile()
{
	return myProjectile.get();
}

void Grapple::LoadJson(const JsonData& someJsonData) // variables moved to GrappleHookProjectile
{
	myMaxDistance = someJsonData["maxDistance"];
	myCoolDown = someJsonData["coolDown"];
	myCoolDownReset = myCoolDown;
}

void Grapple::Setup()
{
}
