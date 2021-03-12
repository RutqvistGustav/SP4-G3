#include "stdafx.h"
#include "Zombie.h"

// JSON
#include <json.hpp>
#include <fstream>

Zombie::Zombie(Scene* aScene)
	: Enemy(aScene)
{
	nlohmann::json data;
	//std::ifstream file(JSON")
	myHealth = 10.0f;
	myDamage = 5.0f;
	mySpeed = 100.0f;
	myMaxSpeed = 200.0f;
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
