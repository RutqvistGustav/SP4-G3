#include "stdafx.h"
#include "HealthBar.h"

#include "RenderCommand.h"
#include "RenderQueue.h"
#include "SpriteWrapper.h"

#include <json.hpp>
#include <fstream>

HealthBar::HealthBar(Scene* aScene)
	: GameObject(aScene)
{
	nlohmann::json data;
	std::ifstream file("JSON/HUD.json");
	data = nlohmann::json::parse(file);
	file.close();
	nlohmann::json healthData = data.at("HealthBar");

	myDistanceFromPlayer.x = healthData.at("DistanceFromPlayerX");
	myDistanceFromPlayer.y = healthData.at("DistanceFromPlayerY");

	mySprite = std::make_shared<SpriteWrapper>("Sprites/HUD/HealthBar.dds");
}

void HealthBar::Update(CU::Vector2<float> aPlayerPosition)
{
	UpdatePosition(aPlayerPosition);
}

void HealthBar::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	aRenderQueue->Queue(RenderCommand(mySprite));
}

void HealthBar::RemoveHP()
{
}

void HealthBar::AddHP()
{
}

void HealthBar::UpdatePosition(CU::Vector2<float> aPlayerPosition)
{
	SetPosition(aPlayerPosition + myDistanceFromPlayer);
}
