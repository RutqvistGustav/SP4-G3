#include "stdafx.h"
#include "PlayerWeaponController.h"

#include "UpdateContext.h"
#include "InputManager.h"
#include "InputInterface.h"

#include "MathHelper.h"
#include "Metrics.h"

#include "GlobalServiceProvider.h"
#include "Player.h"
#include "Scene.h"

#include "Camera.h"
#include "CharacterAnimator.h"

#include "Weapon.h"
#include "WeaponFactory.h"
#include "Shotgun.h"

PlayerWeaponController::PlayerWeaponController(Scene* aScene, Player* aPlayer) :
	myScene(aScene),
	myPlayer(aPlayer)
{}

PlayerWeaponController::~PlayerWeaponController() = default;

void PlayerWeaponController::Init()
{
	myShotgun = myScene->GetGlobalServiceProvider()->GetWeaponFactory()->CreateWeapon("shotgun", myScene, this);
}

void PlayerWeaponController::Update(const float aDeltaTime, UpdateContext & anUpdateContext)
{
	const CU::Vector2<float> aimDirection = ComputeAimDirection(anUpdateContext);

	myShotgun->SetDirection(aimDirection);

	myShotgun->SetPosition(ComputeWeaponPosition());

	myShotgun->Update(aDeltaTime, anUpdateContext);

	if (myPlayer->CanControl())
	{
		if (anUpdateContext.myInputInterface->IsShooting())
		{
			myShotgun->Shoot();
		}
		if (anUpdateContext.myInputInterface->IsBoosting())
		{
			myShotgun->Boost();
		}
	}
}

void PlayerWeaponController::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	myShotgun->Render(aRenderQueue, aRenderContext);
}

CU::Vector2<float> PlayerWeaponController::ComputeWeaponPosition()
{
	const float direction = static_cast<float>(MathHelper::Signum(myShotgun->GetDirection().x));

	CU::Vector2<float> offset = { 0.0f, 0.0f };

	switch (myPlayer->GetCharacterAnimator()->GetState())
	{
	default:
	case CharacterAnimator::State::Idle:
		offset = { 75.0f, -28.0f };
		break;

	case CharacterAnimator::State::Run:
		offset = { 85.0f, -38.0f };
		break;
	}

	return myPlayer->GetPosition() + CU::Vector2(offset.x * direction, offset.y);
}

CU::Vector2<float> PlayerWeaponController::ComputeAimDirection(UpdateContext& anUpdateContext)
{
	myPreviousDirection = myShotgun->GetDirection();
	CU::Vector2<float> direction;
	if (anUpdateContext.myInputInterface->IsMovingLeft_Down())
	{
		direction.x--;
	}
	if (anUpdateContext.myInputInterface->IsMovingRight_Down())
	{
		direction.x++;
	}
	if (direction.x == 0)
	{
		direction = myPreviousDirection;
	}
	return direction;

	//Nedan är om vi vill ha tillbaka att man kan sikta!

	//if (anUpdateContext.myInputInterface->IsUsingController())
	//{
	//	direction = { anUpdateContext.myInputInterface->GetRightStickX(), -anUpdateContext.myInputInterface->GetRightStickY() };
	//}
	//else
	//{
	//	const CU::Vector2<float> mousePosition = {
	//		anUpdateContext.myInput->GetMousePosition().myMouseX * Metrics::GetReferenceSize().x / Metrics::GetRenderSize().x,
	//		anUpdateContext.myInput->GetMousePosition().myMouseY * Metrics::GetReferenceSize().y / Metrics::GetRenderSize().y
	//	};

	//	const CU::Vector2<float> windowRelativePlayerPosition = myPlayer->GetPosition() - myScene->GetCamera()->GetPosition() + Metrics::GetReferenceSize() * 0.5f;

	//	direction = mousePosition - windowRelativePlayerPosition;
	//}

	//const float radians = std::atan2f(direction.y, direction.x);
	//const float step = 2.0f * MathHelper::locPif / 8.0f;

	//const float lockedRadians = std::roundf(radians / step) * step;

	//return CU::Vector2<float>(std::cosf(lockedRadians), std::sinf(lockedRadians));
}

void PlayerWeaponController::ApplyRecoilKnockback(Weapon* aWeapon, float someStrength, bool aShootDown)
{
	if (aShootDown)
	{
		CommonUtilities::Vector2<float> directionDown = {0.0f, 1.0f};
		myPlayer->StopMovement();
		myPlayer->ApplyForce(directionDown *someStrength * -1.0f);
	}
	else
	{
		CommonUtilities::Vector2<float> direction = { aWeapon->GetDirection().x, 0.0f };
		myPlayer->ApplyForce(direction *someStrength * -1.0f);
	}
}

void PlayerWeaponController::ActivatePowerUp(PowerUpType aPowerUpType)
{
	myShotgun->ActivatePowerUp(aPowerUpType);
}

void PlayerWeaponController::DisablePowerUp()
{
	myPlayer->DisablePowerUp();
}

Shotgun* PlayerWeaponController::GetShotgun()
{
	return static_cast<Shotgun*>(myShotgun.get());
}
