#include "stdafx.h"
#include "Zombie.h"
#include "SpriteWrapper.h"
#include "UpdateContext.h"
#include "Player.h"
#include "Collider.h"
// JSON
#include <nlohmann/json.hpp>
#include <fstream>

Zombie::Zombie(Scene* aScene)
	: Enemy(aScene, "Sprites/Enemies/Zombie.dds")
{
	nlohmann::json data;
	std::ifstream file("JSON/EnemyTypes.json");
	data = nlohmann::json::parse(file);
	file.close();

	nlohmann::json zombieData = data.at("Zombie");
	myHealth = zombieData.at("Health");
	myDamage = zombieData.at("Damage");
	mySpeed = zombieData.at("MovementSpeed");
	myMaxSpeed = zombieData.at("MaxSpeedCap");
	myDetectionRange = zombieData.at("DetectionRange");
	myGravity = 3000.0f;
}

Zombie::~Zombie()
{
}

void Zombie::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	// TODO: Jump when near walls
	//		 Climb on eachother?
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

void Zombie::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	GameObject::Render(aRenderQueue, aRenderContext);
}

void Zombie::Movement(const float aDeltaTime)
{
	CU::Vector2<float> direction = myTarget->GetPosition() - myPosition;
	//distance = pow(distance, 0.5f);

	if (myTarget->GetPosition().x < myPosition.x && -myMaxSpeed <= myVelocity.x)
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
	}

	UpdateGravity(aDeltaTime);
	
	direction = myPosition;
	direction += myVelocity * aDeltaTime;
	SetPosition(direction);
}

void Zombie::IdleMovement(const float aDeltaTime)
{
	UpdateGravity(aDeltaTime);
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
	SetPosition(frameMovement);
}


void Zombie::UpdateGravity(const float aDeltaTime)
{
	myVelocity.y += myGravity * aDeltaTime;
}

void Zombie::OnCollision(GameObject* aGameObject)
{
	//Is below needed?
	//CU::Vector2<float> fromOtherToMe(aGameObject->GetPosition() - myPosition);
	//float overlap = 0.0f;

	switch (myCollider->GetCollisionStage())
	{
	case Collider::eCollisionStage::FirstFrame:
	case Collider::eCollisionStage::MiddleFrames:

		if (aGameObject->GetTag() == GameObjectTag::Player)
		{
			myVelocity = CU::Vector2<float>(0.0f, 0.0f);
			//TODO - Add DamagePlayer
		}
		else if (aGameObject->GetTag() != GameObjectTag::Enemy)
		{
			myVelocity = CU::Vector2<float>(myVelocity.x, 0.0f);
		}
		break;
	case Collider::eCollisionStage::NotColliding:
		break;
	default:
		break;
	}
}

void Zombie::OnCollision(TileType aTileType, CU::Vector2<float> anOffset)
{
	switch (myCollider->GetCollisionStage())
	{
	case Collider::eCollisionStage::FirstFrame:
	case Collider::eCollisionStage::MiddleFrames:

		myPosition = myPositionLastFrame - anOffset * 0.01f;

		myVelocity = CU::Vector2<float>(myVelocity.x, 0.0f);
		myGravity = 0;
		break;
	case Collider::eCollisionStage::NotColliding:
		myGravity = 3000;


		break;
	default:
		break;
	}
}

bool Zombie::CheckIdle()
{
	CU::Vector2<float> direction = myTarget->GetPosition() - myPosition;
	float distance = direction.x * direction.x + direction.y * direction.y;

	return (distance <= myDetectionRange * myDetectionRange) ? false : true;
}

void Zombie::ApplyForce(const CU::Vector2<float>& aForce)
{
	myVelocity += aForce;
}
