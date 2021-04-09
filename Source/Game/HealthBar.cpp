#include "stdafx.h"
#include "HealthBar.h"

#include "RenderCommand.h"
#include "RenderQueue.h"
#include "SpriteWrapper.h"
#include "CollisionManager.h"
#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "JsonManager.h"

#include "MathHelper.h"

#include "Health.h"

HealthBar::HealthBar(Scene* aScene, Health* aHealthInterface) :
	GameObject(aScene),
	myHealthInterface(aHealthInterface)
{
	myScene->GetCollisionManager()->RemoveCollider(myCollider);
	myCollider.reset();
}

void HealthBar::Init()
{
	nlohmann::json healthData = GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/HUD.json").at("HealthBar");

	myDistanceFromPlayer.x = healthData.at("DistanceFromPlayerX");
	myDistanceFromPlayer.y = healthData.at("DistanceFromPlayerY");

	mySprite = std::make_shared<SpriteWrapper>("Sprites/HUD/health_frame.dds");
	myHealthBar = std::make_shared<SpriteWrapper>("Sprites/HUD/health.dds");
	myPowerUpFrame = std::make_shared<SpriteWrapper>("Sprites/HUD/Powerup_frame.dds");
	myPowerUpBar = std::make_shared<SpriteWrapper>("Sprites/HUD/Powerup.dds");

	myHealthBar->SetPivot({ 0.5f, 0.5f });
	myPowerUpBar->SetPivot({ 0.5f, 0.5f });
	myPowerUpFrame->SetPivot({ 0.5f, 0.5f });
	mySprite->SetPivot({ 0.5f, 0.5f });

	myPowerupOffset = {0.0f, 30.0f};

	myInitialHealthBarWidth = myHealthBar->GetSize().x;
	myInitialPowerUpBarWidth = myPowerUpBar->GetSize().x;

	mySingleBarSize = 50.0f;
	myHpOffSetX = 22.0f;

	myScene->GetCollisionManager()->RemoveCollider(myCollider);
	myCollider.reset();

	myHealthInterface->Subscribe(this);
}

void HealthBar::Update(CU::Vector2<float> aPlayerPosition)
{
	UpdatePosition(aPlayerPosition);
}

void HealthBar::Render(RenderQueue* const aRenderQueue, RenderContext& /*aRenderContext*/)
{
	aRenderQueue->Queue(RenderCommand(myPowerUpBar));
	aRenderQueue->Queue(RenderCommand(myPowerUpFrame));
	aRenderQueue->Queue(RenderCommand(myHealthBar));
	aRenderQueue->Queue(RenderCommand(mySprite));
}

void HealthBar::ActivatePowerUp(PowerUpType aPowerUpType)
{
	myPowerUpType = aPowerUpType;
}

void HealthBar::UpdatePosition(CU::Vector2<float> aPlayerPosition)
{
	SetPosition(aPlayerPosition + myDistanceFromPlayer);
	myPowerUpFrame->SetPosition(aPlayerPosition + myDistanceFromPlayer + myPowerupOffset);

	myHealthBar->SetPosition(aPlayerPosition + myDistanceFromPlayer);
	myPowerUpBar->SetPosition(aPlayerPosition + myDistanceFromPlayer + myPowerupOffset);
}

void HealthBar::OnEvent(int someNewHealth)
{
	// NOTE: Health has changed
	// TODO: Fix for bars?

	const float percentange = MathHelper::Clamp(someNewHealth / static_cast<float>(myHealthInterface->GetMaxHealth()), 0.0f, 1.0f);

	const CU::Vector2<float> newSize = { myInitialHealthBarWidth * percentange, myHealthBar->GetSize().y };

	myHealthBar->SetTextureRect({ 0.0f, 0.0f, percentange, 1.0f });
	myHealthBar->SetSize(newSize);
}
