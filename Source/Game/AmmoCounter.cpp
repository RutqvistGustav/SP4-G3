#include "stdafx.h"
#include "AmmoCounter.h"

#include "RenderCommand.h"
#include "RenderQueue.h"
#include "SpriteWrapper.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

#include "CollisionManager.h"

AmmoCounter::AmmoCounter(Scene* aScene)
	: GameObject(aScene)
{
	CollisionManager::GetInstance()->RemoveCollider(myCollider);
	myCollider.reset();
}

void AmmoCounter::Init()
{
	nlohmann::json data;
	std::ifstream file("JSON/HUD.json");
	data = nlohmann::json::parse(file);
	file.close();
	nlohmann::json ammoData = data.at("Ammo");

	myCurrentBullets = ammoData.at("AmmoAmount");
	myResetBullets = myCurrentBullets;

	InitSprites(ammoData);
}

void AmmoCounter::Update(CU::Vector2<float> aPlayerPosition)
{
	UpdatePosition(aPlayerPosition);
}

void AmmoCounter::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	switch (myCurrentBullets)
	{
	case AmmoState::Loaded:
	{
		aRenderQueue->Queue(RenderCommand(mySprite));
		break;
	}
	case AmmoState::HalfEmpty:
	{
		//aRenderQueue->Queue(RenderCommand(myHalfState));
		break;
	}
	case AmmoState::Empty:
	{
		// Animation
		Reload();
		break;
	}
	}
}

void AmmoCounter::RemoveBullet()
{
	--myCurrentBullets;
}

void AmmoCounter::Reload()
{
	// Play reload animation
	/*if (myAnimation.GetState() == "End")
	{
		myCurrentBullets = myResetBullets; // sets state to loaded
	}*/
}

void AmmoCounter::UpdatePosition(CU::Vector2<float> aPlayerPosition)
{
	SetPosition(aPlayerPosition + myDistanceFromPlayer);
}

void AmmoCounter::InitSprites(nlohmann::json someData)
{
	myDistanceFromPlayer.x = someData.at("DistanceFromPlayerX");
	myDistanceFromPlayer.y = someData.at("DistanceFromPlayerY");
	CU::Vector2<float> size = { someData.at("SizeX"), someData.at("SizeY") };

	std::string loadedPath = someData.at("LoadedStatePath");
	mySprite = std::make_shared<SpriteWrapper>(loadedPath);
	mySprite->SetSize(size); // temp

	//myHalfState = std::make_shared<SpriteWrapper>("");
	//myEmptyState = std::make_shared<SpriteWrapper>("");
}
