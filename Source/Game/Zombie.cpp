#include "stdafx.h"
#include "Zombie.h"

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
}

void Zombie::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
}
