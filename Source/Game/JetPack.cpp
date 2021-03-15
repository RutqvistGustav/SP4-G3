#include "stdafx.h"
#include "JetPack.h"

// JSON
#include <nlohmann/json.hpp>
#include <fstream>

JetPack::JetPack(Scene* aScene)
	: Enemy(aScene)
{
	nlohmann::json data;
	std::ifstream file("JSON/EnemyTypes.json");
	data = nlohmann::json::parse(file);
	file.close();

	nlohmann::json zombieData = data.at("JetPack");
	myHealth = zombieData.at("Health");
	myDamage = zombieData.at("Damage");
	mySpeed = zombieData.at("MovementSpeed");
	myMaxSpeed = zombieData.at("MaxSpeedCap");
}

JetPack::~JetPack()
{
}

void JetPack::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
}

void JetPack::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
}
