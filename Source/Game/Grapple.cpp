#include "stdafx.h"
#include "Grapple.h"
#include "GrappleHookProjectile.h"

#include "Scene.h"
#include "GlobalServiceProvider.h"

// TODO - Instatiate Hook towards nearest Grapple object
//		- Pull Player in Hook direction
//		- Cancel Hook midair for some momentum
//		- Independant cooldown on the two charges

Grapple::Grapple(Scene* aScene, IWeaponHolder* aWeaponHolder) :
	Weapon(WeaponType::Grapple, aScene, aWeaponHolder)
{}

Grapple::~Grapple() = default;

void Grapple::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myProjectile->Update(aDeltaTime, GetPosition());

	Reload(aDeltaTime);
}

void Grapple::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	myProjectile->Render(aRenderQueue, aRenderContext);
}

void Grapple::Shoot()
{
	if (!myIsLoaded) return;

	myProjectile->SetPosition(GetPosition());
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
	myProjectile = std::make_unique<GrappleHookProjectile>(GetScene(), GetWeaponHolder());
	myProjectile->Init(someJsonData);

	myMaxDistance = someJsonData["maxDistance"];
	myCoolDown = someJsonData["coolDown"];
	myCoolDownReset = myCoolDown;
}

void Grapple::Setup()
{
}
