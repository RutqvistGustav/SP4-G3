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

#include "Weapon.h"
#include "WeaponFactory.h"

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

	myShotgun->SetPosition(myPlayer->GetPosition());

	myShotgun->SetDirection(aimDirection);

	myShotgun->Update(aDeltaTime, anUpdateContext);

	if (anUpdateContext.myInputInterface->IsShooting())
	{
		myShotgun->Shoot();
	}
	if (anUpdateContext.myInputInterface->IsBoosting())
	{
		myShotgun->Boost();
	}
}

void PlayerWeaponController::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	myShotgun->Render(aRenderQueue, aRenderContext);
}

CU::Vector2<float> PlayerWeaponController::ComputeAimDirection(UpdateContext& anUpdateContext)
{
	CU::Vector2<float> direction;

	if (anUpdateContext.myInputInterface->IsUsingController())
	{
		direction = { anUpdateContext.myInputInterface->GetRightStickX(), -anUpdateContext.myInputInterface->GetRightStickY() };
	}
	else
	{
		const CU::Vector2<float> mousePosition = {
			anUpdateContext.myInput->GetMousePosition().myMouseX * Metrics::GetReferenceSize().x / Metrics::GetRenderSize().x,
			anUpdateContext.myInput->GetMousePosition().myMouseY * Metrics::GetReferenceSize().y / Metrics::GetRenderSize().y
		};

		const CU::Vector2<float> windowRelativePlayerPosition = myPlayer->GetPosition() - myScene->GetCamera()->GetPosition() + Metrics::GetReferenceSize() * 0.5f;

		direction = mousePosition - windowRelativePlayerPosition;
	}

	const float radians = std::atan2f(direction.y, direction.x);
	const float step = 2.0f * MathHelper::locPif / 8.0f;

	const float lockedRadians = std::roundf(radians / step) * step;

	return CU::Vector2<float>(std::cosf(lockedRadians), std::sinf(lockedRadians));
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
		myPlayer->ApplyForce(aWeapon->GetDirection() * someStrength * -1.0f);
	}
}
