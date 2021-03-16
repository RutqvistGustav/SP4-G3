#include "stdafx.h"
#include "Zombie.h"
#include "SpriteWrapper.h"

// JSON
#include <nlohmann/json.hpp>
#include <fstream>

Zombie::Zombie(Scene* aScene)
	: Enemy(aScene)
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
	
	//Temp Variable, Remove when Target is available!
	CU::Vector2<float> targetPosition = {960.0f, 540.0f};
	Movement(aDeltaTime, targetPosition);

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
		myVelocity += direction.GetNormalized() * mySpeed * aDeltaTime;
	}
	if (aTarget.x > myPosition.x && myVelocity.x <= myMaxSpeed)
	{
		myVelocity += direction.GetNormalized() * mySpeed * aDeltaTime;
	}

	myPosition += myVelocity * aDeltaTime;
	mySprite->SetPosition(myPosition);
}
