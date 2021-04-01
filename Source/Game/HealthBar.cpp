#include "stdafx.h"
#include "HealthBar.h"

#include "RenderCommand.h"
#include "RenderQueue.h"
#include "SpriteWrapper.h"
#include "CollisionManager.h"
#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "JsonManager.h"

#include <nlohmann/json.hpp>

HealthBar::HealthBar(Scene* aScene)
	: GameObject(aScene)
{
	myScene->GetCollisionManager()->RemoveCollider(myCollider);
	myCollider.reset();
}

void HealthBar::Init()
{
	nlohmann::json healthData = GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/HUD.json").at("HealthBar");

	myDistanceFromPlayer.x = healthData.at("DistanceFromPlayerX");
	myDistanceFromPlayer.y = healthData.at("DistanceFromPlayerY");

	mySprite = std::make_shared<SpriteWrapper>("Sprites/HUD/temps/HUD frame.dds");
	myHealthBar = std::make_shared<SpriteWrapper>("Sprites/HUD/temps/HealthBar.dds");
	myPowerUpBar = std::make_shared<SpriteWrapper>("Sprites/HUD/temps/PowerUpBar.dds");

	//CU::Vector2<float> scale = { 250.0f,100.0f };
	//mySprite->SetSize(scale);
	//myHealthBar->SetSize(scale);
	//myPowerUpBar->SetSize(scale);

	myReducedHealth = CU::Vector2<float>();
	myReducedPowerUp = CU::Vector2<float>();

	myScene->GetCollisionManager()->RemoveCollider(myCollider);
	myCollider.reset();
}

void HealthBar::Update(CU::Vector2<float> aPlayerPosition)
{
	UpdatePosition(aPlayerPosition);
}

void HealthBar::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	aRenderQueue->Queue(RenderCommand(myHealthBar));
	aRenderQueue->Queue(RenderCommand(myPowerUpBar));
	aRenderQueue->Queue(RenderCommand(mySprite));
}

void HealthBar::RemoveHP()
{
	CU::Vector2<float> reducedHealth = myHealthBar->GetSize();
	myReducedHealth.x -= 22.0f;
	reducedHealth.x -= 50.0f;
	myHealthBar->SetSize(reducedHealth);
}

void HealthBar::AddHP()
{
	// restore size of hp bar.
}

void HealthBar::ActivatePowerUp(PowerUpType aPowerUpType)
{
	myPowerUpType = aPowerUpType;
}

void HealthBar::UpdatePosition(CU::Vector2<float> aPlayerPosition)
{
	SetPosition(aPlayerPosition + myDistanceFromPlayer);
	myHealthBar->SetPosition(aPlayerPosition + myDistanceFromPlayer + myReducedHealth);
	myPowerUpBar->SetPosition(aPlayerPosition + myDistanceFromPlayer);
}
