#include "stdafx.h"
#include "PlayerWeaponController.h"

#include "UpdateContext.h"
#include "InputManager.h"
#include "InputInterface.h"
#include "JsonManager.h"

#include "MathHelper.h"
#include "Metrics.h"

#include "Player.h"

#include "Grapple.h"
#include "GrappleHookProjectile.h"
#include "Weapon.h"
#include "WeaponFactory.h"

PlayerWeaponController::PlayerWeaponController(const WeaponFactory* aWeaponFactory, Player* aPlayer)
	: myPlayer(aPlayer)
{
	// NOTE: For now it seems we are only going to ever have 2 weapons so no need to get fancy
	myGrapple = std::static_pointer_cast<Grapple> (aWeaponFactory->CreateWeapon("grapple", this));
	myShotgun = aWeaponFactory->CreateWeapon("shotgun", this);
}

PlayerWeaponController::~PlayerWeaponController() = default;

void PlayerWeaponController::Init()
{
	myGrapple->InitGameObjects(myPlayer->GetScene());
}

void PlayerWeaponController::Update(const float aDeltaTime, UpdateContext & anUpdateContext)
{
	const CU::Vector2<float> aimDirection = ComputeAimDirection(anUpdateContext);

	myGrapple->SetDirection(aimDirection);
	myShotgun->SetDirection(aimDirection);

	myGrapple->Update(aDeltaTime, anUpdateContext, myPlayer->GetPosition());
	myShotgun->Update(aDeltaTime, anUpdateContext, myPlayer->GetPosition());

	if (anUpdateContext.myInputInterface->IsGrappling())
	{
		myGrapple->Shoot(myPlayer->GetPosition());
	}
	else if (anUpdateContext.myInputInterface->IsShooting())
	{
		myShotgun->Shoot(myPlayer->GetPosition());
	}
}

void PlayerWeaponController::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	myGrapple->Render(aRenderQueue, aRenderContext);
	myShotgun->Render(aRenderQueue, aRenderContext);
}

CU::Vector2<float> PlayerWeaponController::ComputeAimDirection(UpdateContext& anUpdateContext)
{
	// TODO: Figure out direction of weapons and update
	// NOTE: Will have to be changed, this is just to test with a mouse

	const CU::Vector2<float> mousePosition = {
		anUpdateContext.myInput->GetMousePosition().myMouseX * Metrics::GetReferenceSize().x / Metrics::GetRenderSize().x,
		anUpdateContext.myInput->GetMousePosition().myMouseY * Metrics::GetReferenceSize().y / Metrics::GetRenderSize().y
	};

	const CU::Vector2<float> direction = mousePosition - myPlayer->GetPosition();

	const float radians = std::atan2f(direction.y, direction.x);
	const float step = 2.0f * MathHelper::locPif / 8.0f;

	const float lockedRadians = std::roundf(radians / step) * step;

	return CU::Vector2<float>(std::cosf(lockedRadians), std::sinf(lockedRadians));
}

void PlayerWeaponController::ApplyRecoilKnockback(Weapon* aWeapon, float someStrength)
{
	myPlayer->ApplyForce(aWeapon->GetDirection() * someStrength * -1.0f);
}

void PlayerWeaponController::OnGrappleHit(const CU::Vector2<float>& aTargetPosition, const CU::Vector2<float>& aGrapplingDirection)
{
	myPlayer->StartGrappling(aTargetPosition, aGrapplingDirection);
}

void PlayerWeaponController::StopGrappling()
{
	myGrapple->GetProjectile()->ResetProjectile();
}
