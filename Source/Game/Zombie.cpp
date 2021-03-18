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
	myGravity = 3000.0f;
}

Zombie::~Zombie()
{
}

void Zombie::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	// TODO: Get a Target
	//		 Follow Target
	//		 Jump when near walls
	//		 Climb on eachother?

	Movement(aDeltaTime, anUpdateContext.myPlayer->GetPosition());
	GameObject::Update(aDeltaTime, anUpdateContext);
}

void Zombie::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	GameObject::Render(aRenderQueue, aRenderContext);
}

void Zombie::Movement(const float aDeltaTime, const CU::Vector2<float>& aTarget)
{
	CU::Vector2<float> direction = aTarget - myPosition;
	//float distance = direction.x * direction.x + direction.y * direction.y;
	//distance = pow(distance, 0.5f);

	if (aTarget.x < myPosition.x && -myMaxSpeed <= myVelocity.x)
	{
		if (myVelocity.x > 20.0f) myVelocity.x *= pow(0.001, aDeltaTime); // Brake Movement
		else
		{
			myVelocity.x += direction.GetNormalized().x * mySpeed * aDeltaTime * 10.0f;
		}
	}
	if (aTarget.x > myPosition.x && myVelocity.x <= myMaxSpeed)
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

void Zombie::UpdateGravity(const float aDeltaTime)
{
	myVelocity.y += myGravity * aDeltaTime;
}

void Zombie::OnCollision(GameObject* aGameObject)
{
	CU::Vector2<float> fromOtherToMe(myPosition - aGameObject->GetPosition());
	float overlap = 0.0f;

	switch (myCollider->GetCollisionStage())
	{
	case Collider::eCollisionStage::FirstFrame:
	case Collider::eCollisionStage::MiddleFrames:



		if (myCollider->GetIsCube())
		{
			myPosition = myPositionLastFrame + fromOtherToMe.GetNormalized() * 0.01f;
			myPosition.y = aGameObject->GetPosition().y - aGameObject->GetCollider()->GetRadius() - myCollider->GetRadius();
		}
		else
		{
			overlap = fromOtherToMe.Length() - myCollider->GetRadius() - aGameObject->GetCollider()->GetRadius();
			myPosition -= overlap * fromOtherToMe.GetNormalized();
		}


		myVelocity = CU::Vector2<float>(myVelocity.x, 0.0f);
		myGravity = 0;
		//myCollider->SetPos(myPosition);

		break;
	case Collider::eCollisionStage::NotColliding:
		myGravity = 3000;
		break;
	default:
		break;
	}
}
