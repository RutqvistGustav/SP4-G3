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
	: Enemy(aScene, anEnemyType, "Sprites/Enemies/Zombie.dds")
{
	InitEnemyJsonValues(aType);
	myCharacterAnimator.SetState(CharacterAnimator::State::Idle);
	myCharacterAnimator.ApplyToSprite(mySprite);
}

Zombie::~Zombie() = default;

void Zombie::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myPreviousVelocity = myPhysicsController.GetVelocity();
	// TODO: Change Direction Near Walls
	if (myTarget != nullptr)
	{
		if (CheckIdle())
		{
			IdleMovement(aDeltaTime);
			myCharacterAnimator.SetState(CharacterAnimator::State::Idle);
		}
		else
		{
			Movement(aDeltaTime);
		}
	}

	Enemy::Update(aDeltaTime, anUpdateContext);
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

	velocity.x *= std::powf(0.001f, aDeltaTime);
	velocity.x += direction.GetNormalized().x * mySpeed * aDeltaTime * 10.0f;

	myPhysicsController.SetVelocity(velocity);

	/*if (myTarget->GetPosition().x < myPosition.x)
	{
		if (myVelocity.x > 20.0f) myVelocity.x *= pow(0.001, aDeltaTime); // Brake Movement
		else
		{
			myVelocity.x += direction.GetNormalized().x * mySpeed * aDeltaTime * 10.0f;
		}
	}
	if (myTarget->GetPosition().x > myPosition.x && myVelocity.x <= myMaxSpeed)
	{
		if (myVelocity.x < -20.0f) myVelocity.x *= pow(0.001, aDeltaTime); // Brake Movement
		else
		{
			myVelocity.x += direction.GetNormalized().x * mySpeed * aDeltaTime * 10.0f;
		}
	}*/
}

void Zombie::IdleMovement(const float aDeltaTime)
{
	CU::Vector2<float> velocity = myPhysicsController.GetVelocity();
	
	const float direction = velocity.x >= 0.0f ? 1.0f : -1.0f;
	velocity.x *= std::powf(0.001f, aDeltaTime);
	velocity.x += direction * mySpeed * aDeltaTime * 10.0f;

	if (myPhysicsController.IsAgainstWall())
	{
		velocity.x = -myPreviousVelocity.x * 0.01f;
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

bool Zombie::CheckIdle()
{
	if (myPosition.y > myTarget->GetPosition().y - 50.f && myPosition.y < myTarget->GetPosition().y + 25.0f)
	{
		CU::Vector2<float> direction = myTarget->GetPosition() - myPosition;
		const float distance = direction.LengthSqr();
		
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
