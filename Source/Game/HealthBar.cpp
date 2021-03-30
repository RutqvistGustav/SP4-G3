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

	mySprite = std::make_shared<SpriteWrapper>("Sprites/HUD/HealthBar.dds");

	myScene->GetCollisionManager()->RemoveCollider(myCollider);
	myCollider.reset();
}

void HealthBar::Update(CU::Vector2<float> aPlayerPosition)
{
	UpdatePosition(aPlayerPosition);
}

void HealthBar::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	aRenderQueue->Queue(RenderCommand(mySprite));
}

void HealthBar::OnCollision(GameObject*)
{
}

void HealthBar::RemoveHP()
{
	// decrease size of hp bar.
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
}
