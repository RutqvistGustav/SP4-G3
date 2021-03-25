#include "stdafx.h"
#include "Zombie.h"
#include "SpriteWrapper.h"
#include "UpdateContext.h"
#include "Player.h"
#include "Collider.h"
#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "JsonManager.h"
#include "Health.h"
#include "DamageVolume.h"
// JSON
#include <nlohmann/json.hpp>
#include <fstream>

Zombie::Zombie(Scene* aScene)
	: Enemy(aScene, "Sprites/Enemies/Zombie.dds")
{
	nlohmann::json data = GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/EnemyTypes.json");
	nlohmann::json zombieData = data.at("Zombie");
	myHealth = std::make_unique<Health>(zombieData.at("Health"));
	myHealth->SetInvincibilityTimer(zombieData.at("Invincibility"));
	myDamage = zombieData.at("Damage");
	mySpeed = zombieData.at("MovementSpeed");
	myMaxSpeed = zombieData.at("MaxSpeedCap");
	myDetectionRange = zombieData.at("DetectionRange");
	myKnockback = zombieData.at("KnockBack");
	myGravity = 3000.0f;
}

Zombie::~Zombie()
{
}

void Zombie::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
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

void Zombie::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	GameObject::Render(aRenderQueue, aRenderContext);
}

void Zombie::Movement(const float aDeltaTime)
{
	CU::Vector2<float> direction = myTarget->GetPosition() - myPosition;
	//distance = pow(distance, 0.5f);
	UpdateGravity(aDeltaTime);

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


	direction = myPosition;
	direction += myVelocity * aDeltaTime;
	SetPosition(direction);
}

void Zombie::IdleMovement(const float aDeltaTime)
{
	//TODO - Change Direction when hitting a wall
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
	if (myApplyGravity)
	{
		myVelocity.y += myGravity * aDeltaTime;
	}
	else
	{
		myVelocity.y = 0.0f;
	}
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

			Player* player = static_cast<Player*>(myTarget.get());
			player->TakeDamage(myDamage);
			player->ApplyForce((player->GetPosition() - GetPosition()).GetNormalized() * myKnockback);
			//TODO - Add DamagePlayer
		}
		//if (aGameObject->GetTag() != GameObjectTag::Enemy)
		//{
		//	myVelocity = CU::Vector2<float>(myVelocity.x, 0.0f);
		//}
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
