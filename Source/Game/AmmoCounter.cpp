#include "stdafx.h"
#include "AmmoCounter.h"

#include "RenderCommand.h"
#include "RenderQueue.h"
#include "SpriteWrapper.h"
#include "Scene.h"
#include "Shotgun.h"

#include <nlohmann/json.hpp>
#include <fstream>
#include <string>

#include "CollisionManager.h"

AmmoCounter::AmmoCounter(Scene* aScene, Shotgun* aShotgun)
	: GameObject(aScene),
	myShotgun(aShotgun)
{
	aScene->GetCollisionManager()->RemoveCollider(myCollider);
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
	myShotgun->Subscribe(this);
}

void AmmoCounter::Update(CU::Vector2<float> aPlayerPosition)
{
	UpdatePosition(aPlayerPosition);
}

void AmmoCounter::Render(RenderQueue* const aRenderQueue, RenderContext& /*aRenderContext*/)
{
	aRenderQueue->Queue(RenderCommand(mySprite));
	aRenderQueue->Queue(RenderCommand(mySecondSprite));
}

void AmmoCounter::RemoveBullet()
{
	if (myCurrentBullets == 1)
	{
		Tga2D::CColor inactiveColor = mySecondSprite->GetColor();
		inactiveColor.myA = 0.0f;
		mySecondSprite->SetColor(inactiveColor);
	}
	else if ( myCurrentBullets == 0)
	{
		Tga2D::CColor inactiveColor = mySprite->GetColor();
		inactiveColor.myA = 0.0f;
		mySprite->SetColor(inactiveColor);
	}
	else
	{
		Reload();
	}
}

void AmmoCounter::Reload()
{
	myCurrentBullets = myResetBullets;

	Tga2D::CColor activeColor = mySecondSprite->GetColor();
	activeColor.myA = 1.0f;
	mySprite->SetColor(activeColor);
	mySecondSprite->SetColor(activeColor);
}

void AmmoCounter::UpdatePosition(CU::Vector2<float> aPlayerPosition)
{
	SetPosition(aPlayerPosition + myDistanceFromPlayer);
	mySecondSprite->SetPosition(aPlayerPosition + myDistanceFromPlayer + mySpriteDistance);
}

void AmmoCounter::InitSprites(nlohmann::json someData)
{
	myDistanceFromPlayer.x = someData.at("DistanceFromPlayerX");
	myDistanceFromPlayer.y = someData.at("DistanceFromPlayerY");
	CU::Vector2<float> size = { someData.at("SizeX"), someData.at("SizeY") };

	std::string spritepath = someData.at("SpritePath");
	mySprite = std::make_shared<SpriteWrapper>(spritepath);
	mySprite->SetLayer(49);

	mySecondSprite = std::make_shared<SpriteWrapper>(spritepath);
	mySecondSprite->SetLayer(49);
	CU::Vector2<float> new_pos = mySecondSprite->GetPosition();

	mySpriteDistance.x = someData.at("DistanceBetweenBullets");
	new_pos.x += mySpriteDistance.x;
	mySecondSprite->SetPosition(new_pos);
}

void AmmoCounter::OnEvent(int anAmmoAmount)
{
	myCurrentBullets = anAmmoAmount;
	RemoveBullet();
}
