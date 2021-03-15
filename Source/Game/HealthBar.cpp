#include "stdafx.h"
#include "RenderCommand.h"
#include "RenderQueue.h"
#include "HealthBar.h"
#include "SpriteWrapper.h"

#include <nlohmann/json.hpp>
#include <fstream>

HealthBar::HealthBar(Scene* aScene)
	: GameObject(aScene)
{
	nlohmann::json data;
	std::ifstream file("JSON/HUD.json");
	data = nlohmann::json::parse(file);
	file.close();

	myDistanceFromPlayer.x = data.at("HealthBar").at("DistanceFromPlayerX");
	myDistanceFromPlayer.y = data.at("HealthBar").at("DistanceFromPlayerY");

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
