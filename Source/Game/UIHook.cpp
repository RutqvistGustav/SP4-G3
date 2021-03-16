#include "stdafx.h"
#include "UIHook.h"

#include "RenderCommand.h"
#include "RenderQueue.h"
#include "SpriteWrapper.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

UIHook::UIHook(Scene* aScene)
	: GameObject(aScene)
{
}

void UIHook::Init()
{
	nlohmann::json data;
	std::ifstream file("JSON/HUD.json");
	data = nlohmann::json::parse(file);
	file.close();
	nlohmann::json hookData = data.at("GrapplingHook");

	myDistanceFromPlayer.x = hookData.at("DistanceFromPlayerX");
	myDistanceFromPlayer.y = hookData.at("DistanceFromPlayerY");

	std::string spritePath = hookData.at("HookPath");
	mySprite = std::make_shared<SpriteWrapper>(spritePath);
	mySprite->SetSize({ hookData.at("SizeX"), hookData.at("SizeY") });

	//std::string highlightSpritePath = hookData.at("HighlightHookPath");
	//mySpriteHighlighed = std::make_shared<SpriteWrapper>(highlightSpritePath);
}

void UIHook::Update(CU::Vector2<float> aPlayerPosition)
{
	UpdatePosition(aPlayerPosition);
}

void UIHook::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	if (myIsHighlightActive == true)
	{
		//aRenderQueue->Queue(RenderCommand(mySpriteHighlighed));
	}
	else
	{
		aRenderQueue->Queue(RenderCommand(mySprite));
	}
}

void UIHook::SetHighlight(const bool aIsActive)
{
	myIsHighlightActive = aIsActive;
}

void UIHook::UpdatePosition(CU::Vector2<float> aPlayerPosition)
{
	SetPosition(aPlayerPosition + myDistanceFromPlayer);
}
