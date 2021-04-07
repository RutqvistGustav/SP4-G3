#include "stdafx.h"
#include "Zombie.h"
#include "SpriteWrapper.h"
#include "UpdateContext.h"
#include "Player.h"
#include "Collider.h"
#include "Scene.h"
#include "Health.h"

Zombie::Zombie(Scene* aScene, const std::string& aType)
	: Enemy(aScene, "Sprites/Enemies/Zombie.dds")
{
	InitEnemyJsonValues(aType);
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
	float direction = velocity.x >= 0.0f ? 1.0f : -1.0f;
	
	velocity.x *= std::powf(0.001f, aDeltaTime);
	velocity.x += direction * mySpeed * aDeltaTime * 10.0f;

	if (myPhysicsController.IsAgainstWall())
	{
		velocity.x = -myPreviousVelocity.x * 0.01f;
	}

	myPhysicsController.SetVelocity(velocity);
	/*UpdateGravity(aDeltaTime);
	if (myVelocity.x > 0.0f)
	{
		myVelocity.x = myMaxSpeed * 0.5f;
	}
	else if (myVelocity.x < 0.0f)
	{
		myVelocity.x = -myMaxSpeed * 0.5f;
	}
	CU::Vector2<float> frameMovement = myPosition;
	frameMovement += myVelocity * aDeltaTime;
	SetPosition(frameMovement);*/
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
