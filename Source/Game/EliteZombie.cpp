#include "stdafx.h"
#include "EliteZombie.h"
#include "SpriteWrapper.h"
#include "UpdateContext.h"
#include "Player.h"
#include "Collider.h"
#include "Scene.h"
#include "Health.h"

EliteZombie::EliteZombie(Scene* aScene)
	: Enemy(aScene, "Sprites/Enemies/Zombie.dds")
{
	std::string type = "EliteZombie";
	InitEnemyJsonValues(type);
	//Temp to see difference
	mySprite->SetColor({0.5f, 0.0f, 0.0f, 1.0f});
	myGravity = 3000.0f;
}

EliteZombie::~EliteZombie()
{
}

void EliteZombie::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	// TODO: Jump when near walls
	//		 Climb on eachother?
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
		GameObject::Update(aDeltaTime, anUpdateContext);
	}
}

void EliteZombie::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	GameObject::Render(aRenderQueue, aRenderContext);
}

void EliteZombie::Movement(const float aDeltaTime)
{
	CU::Vector2<float> direction = myTarget->GetPosition() - myPosition;

	UpdateGravity(aDeltaTime);

	if (myTarget->GetPosition().x < myPosition.x && -myMaxSpeed <= myVelocity.x)
	{
		if (myVelocity.x > 20.0f) myVelocity.x *= pow(0.001, aDeltaTime); // Brake Movement
		else
		{
			myVelocity.x += direction.GetNormalized().x * mySpeed * aDeltaTime;
		}
	}
	if (myTarget->GetPosition().x > myPosition.x && myVelocity.x <= myMaxSpeed)
	{
		if (myVelocity.x < -20.0f) myVelocity.x *= pow(0.001, aDeltaTime); // Brake Movement
		else
		{
			myVelocity.x += direction.GetNormalized().x * mySpeed * aDeltaTime;
		}
	}

	direction = myPosition;
	direction += myVelocity * aDeltaTime;
	SetPosition(direction);
}

void EliteZombie::IdleMovement(const float aDeltaTime)
{
	//TODO - Change Direction when hitting a wall
	UpdateGravity(aDeltaTime);
	if (myVelocity.x > mySpeed)
	{
		myVelocity.x = myMaxSpeed * 0.5f;
	}
	else if (myVelocity.x < -mySpeed)
	{
		myVelocity.x = -myMaxSpeed * 0.5f;
	}
	CU::Vector2<float> frameMovement = myPosition;
	frameMovement += myVelocity * aDeltaTime;
	SetPosition(frameMovement);
}


void EliteZombie::UpdateGravity(const float aDeltaTime)
{
	if (myApplyGravity)
	{
		myVelocity.y += myGravity * aDeltaTime;
	}
}

void EliteZombie::OnCollision(GameObject* aGameObject)
{
	switch (myCollider->GetCollisionStage())
	{
	case Collider::eCollisionStage::FirstFrame:
	case Collider::eCollisionStage::MiddleFrames:

		if (aGameObject->GetTag() == GameObjectTag::Player)
		{
			myVelocity = CU::Vector2<float>(0.0f, 0.0f);

			Player* player = static_cast<Player*>(myTarget.get());
			player->TakeDamage(myDamage);

			CU::Vector2<float> direction = (player->GetPosition() - GetPosition()).GetNormalized();
			//if (direction.y > -0.2f && direction.y < 0.2f)
			//{
			//	player->ApplyForce(direction * myKnockback);
			//}
		}
		break;
	case Collider::eCollisionStage::NotColliding:
		break;
	default:
		break;
	}
}

void EliteZombie::OnCollision(TileType aTileType, CU::Vector2<float> anOffset)
{
	switch (myCollider->GetCollisionStage())
	{
	case Collider::eCollisionStage::FirstFrame:
	case Collider::eCollisionStage::MiddleFrames:

		myPosition = myPositionLastFrame - anOffset * 0.05f;

		myVelocity = CU::Vector2<float>(myVelocity.x, 0.0f);
		myApplyGravity = false;
		break;
	case Collider::eCollisionStage::NotColliding:
		myApplyGravity = true;
		break;
	default:
		break;
	}
}

bool EliteZombie::CheckIdle()
{
	CU::Vector2<float> direction = myTarget->GetPosition() - myPosition;
	float distance = direction.x * direction.x + direction.y * direction.y;

	if (direction.y)
	{

	}

	return (distance <= myDetectionRange * myDetectionRange) ? false : true;
}

void EliteZombie::ApplyForce(const CU::Vector2<float>& aForce)
{
	myVelocity += aForce;
}
