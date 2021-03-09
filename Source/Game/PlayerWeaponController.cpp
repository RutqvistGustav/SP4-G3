#include "stdafx.h"
#include "PlayerWeaponController.h"

#include "UpdateContext.h"
#include "InputInterface.h"

#include "Player.h"

#include "Weapon.h"
#include "WeaponFactory.h"

PlayerWeaponController::PlayerWeaponController(const WeaponFactory* aWeaponFactory, Player* aPlayer)
	: myPlayer(aPlayer)
{
	// NOTE: For now it seems we are only going to ever have 2 weapons so no need to get fancy
	myGrapple = aWeaponFactory->CreateWeapon("grapple", this);
	myShotgun = aWeaponFactory->CreateWeapon("shotgun", this);
}

PlayerWeaponController::~PlayerWeaponController() = default;

void PlayerWeaponController::Update(const float aDeltaTime, UpdateContext & anUpdateContext)
{
	// TODO: Figure out direction of weapons and update

	myGrapple->Update(aDeltaTime, anUpdateContext);
	myShotgun->Update(aDeltaTime, anUpdateContext);

	if (anUpdateContext.myInputInterface->IsGrappling())
	{
		myGrapple->Shoot();
	}
	else if (anUpdateContext.myInputInterface->IsShooting())
	{
		myShotgun->Shoot();
	}
}

void PlayerWeaponController::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	myGrapple->Render(aRenderQueue, aRenderContext);
	myShotgun->Render(aRenderQueue, aRenderContext);
}

void PlayerWeaponController::ApplyRecoilKnockback(Weapon* aWeapon, float someStrength)
{
	myPlayer->ApplyForce(aWeapon->GetDirection() * someStrength * -1.0f);
}
