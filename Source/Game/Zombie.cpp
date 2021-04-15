#include "stdafx.h"
#include "Zombie.h"
#include "SpriteWrapper.h"
#include "UpdateContext.h"
#include "Player.h"
#include "Collider.h"
#include "Scene.h"
#include "Health.h"
#include "GlobalServiceProvider.h"
#include "AudioManager.h"

Zombie::Zombie(Scene* aScene, EnemyType anEnemyType, const std::string& aType)
	: Enemy(aScene, anEnemyType)
{
	myCharacterAnimator.SetState(CharacterAnimator::State::Idle);
	myCharacterAnimator.ApplyToSprite(mySprite);

	InitEnemyJsonValues(aType);
}

Zombie::~Zombie() = default;

void Zombie::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	// TODO: Change Direction Near Walls
	if (myTarget != nullptr && !myHealth->IsDead())
	{
		if (CheckIdle())
		{
			IdleMovement(aDeltaTime);
		}
		else
		{
			Movement(aDeltaTime);
		}
	}

	Enemy::Update(aDeltaTime, anUpdateContext);

	if (std::abs(myPhysicsController.GetVelocity().x) >= 1.0f && !myIsPlayerInRange)
	{
		myCharacterAnimator.SetState(CharacterAnimator::State::Run);
	}
	else if (std::abs(myPhysicsController.GetVelocity().x) < 1.0f && !myIsPlayerInRange)
	{
		myCharacterAnimator.SetState(CharacterAnimator::State::Idle);
	}
}

void Zombie::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	Enemy::Render(aRenderQueue, aRenderContext);
}

void Zombie::Movement(const float aDeltaTime)
{
	PlayTriggeredSoundOnce();

	const CU::Vector2<float> direction = myTarget->GetPosition() - myPosition;
	CU::Vector2<float> velocity = myPhysicsController.GetVelocity();

	velocity.x *= std::powf(myMaxSpeed, aDeltaTime);

	if (!myIsPlayerInRange)
	{
		velocity.x += direction.GetNormalized().x * mySpeed * aDeltaTime * 10.0f;
	}

	if (
		(velocity.x < 0.0f && myPhysicsController.IsFloorOvershootLeft()) ||
		(velocity.x > 0.0f && myPhysicsController.IsFloorOvershootRight())
		)
	{
		velocity.x *= -1.0f;
	}

	myPhysicsController.SetVelocity(velocity);
}

void Zombie::IdleMovement(const float aDeltaTime)
{
	if (myShouldRoam)
	{
		CU::Vector2<float> velocity = myPhysicsController.GetVelocity();

		const float direction = velocity.x >= 0.0f ? 1.0f : -1.0f;
		velocity.x *= std::powf(myRoamMaxSpeed, aDeltaTime);
		velocity.x += direction * mySpeed * aDeltaTime * 10.0f;

		if (myPhysicsController.IsAgainstWall())
		{
			velocity.x = -myCharacterAnimator.GetDirection();
		}

		if (
			(velocity.x < 0.0f && myPhysicsController.IsFloorOvershootLeft()) ||
			(velocity.x > 0.0f && myPhysicsController.IsFloorOvershootRight())
			)
		{
			velocity.x *= -1.0f;
		}

		myPhysicsController.SetVelocity(velocity);
	}
}

bool Zombie::CheckIdle()
{
	if (myPosition.y > myTarget->GetPosition().y - 50.f && myPosition.y < myTarget->GetPosition().y + 25.0f)
	{
		CU::Vector2<float> direction = myTarget->GetPosition() - myPosition;
		const float distance = direction.LengthSqr();
		
		myShouldRoam = true;
		return distance > (myDetectionRange * myDetectionRange);
	}
	return true;
}

void Zombie::PlayTriggeredSoundOnce()
{
	if (myHasSoundPlayOnce == false)
	{
		GetScene()->GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Enemy/Zombie_Growl_03.mp3");
		myHasSoundPlayOnce = true;
	}
}
