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

	mySprite = std::make_shared<SpriteWrapper>(healthData.at("HpFramePath"));
	mySprite->SetLayer(50);
	myHealthBar = std::make_shared<SpriteWrapper>(healthData.at("HpBarPath"));
	myHealthBar->SetLayer(49);
	myPowerUpFrame = std::make_shared<SpriteWrapper>(healthData.at("PowerupFramePath"));
	myPowerUpFrame->SetLayer(50);
	myPowerUpBar = std::make_shared<SpriteWrapper>(healthData.at("PowerupBarPath"));
	myPowerUpBar->SetLayer(49);

	nlohmann::json playerData = GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/Weapons.json").at("shotgun");
	myBerserkDuration = playerData.at("Berserk").at("Duration");
	myBerserkDurationReset = myBerserkDuration;

	CU::Vector2<float> center = { 0.5f, 0.5f };
	myHealthBar->SetPivot({ 0.0f,0.5f });
	myPowerUpBar->SetPivot(center);
	myPowerUpFrame->SetPivot(center);
	mySprite->SetPivot(center);

	myInitialHealthBarWidth = myHealthBar->GetSize().x;
	myInitialPowerUpBarWidth = myPowerUpBar->GetSize().x;

	myHealthBarOffSet.x = myInitialHealthBarWidth / 2;
	myPowerupFrameOffSet = {0.0f, 30.0f};

	myScene->GetCollisionManager()->RemoveCollider(myCollider);
	myCollider.reset();

	myHealthInterface->Subscribe(this);
}

void HealthBar::Update(const float aDeltaTime, CU::Vector2<float> aPlayerPosition)
{
	ReducePowerUpAmount(aDeltaTime);
	UpdatePosition(aPlayerPosition);
}

void HealthBar::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	aRenderQueue->Queue(RenderCommand(myPowerUpBar));
	aRenderQueue->Queue(RenderCommand(myPowerUpFrame));
	aRenderQueue->Queue(RenderCommand(myHealthBar));
	aRenderQueue->Queue(RenderCommand(mySprite));
}

void HealthBar::ActivatePowerUp(PowerUpType aPowerUpType)
{
	myPowerUpType = aPowerUpType;
	myIsPowerUpActive = true;
}

void HealthBar::ReducePowerUpAmount(const float aDeltaTime)
{
	if (myIsPowerUpActive)
	{
		myBerserkDuration -= aDeltaTime;
		if (myBerserkDuration > 0)
		{
			const float percentange = MathHelper::Clamp(myBerserkDuration / myBerserkDurationReset, 0.0f, 1.0f);
			const CU::Vector2<float> newSize = { myInitialPowerUpBarWidth * percentange, myPowerUpBar->GetSize().y };

			myPowerupBarOffSet.x = (myInitialPowerUpBarWidth - myPowerUpBar->GetSize().x) * 0.5f;

			myPowerUpBar->SetTextureRect({ 0.0f, 0.0f, percentange, 1.0f });
			myPowerUpBar->SetSize(newSize);
		}
		else
		{
			myIsPowerUpActive = false;
			myBerserkDuration = myBerserkDurationReset;
			myPowerupBarOffSet.x = 0.0f;
			myPowerUpBar->SetSize({ myInitialPowerUpBarWidth, myPowerUpBar->GetSize().y });
		}
	}
}

void HealthBar::UpdatePosition(CU::Vector2<float> aPlayerPosition)
{
	SetPosition(aPlayerPosition + myDistanceFromPlayer);
	myPowerUpFrame->SetPosition(aPlayerPosition + myDistanceFromPlayer + myPowerupFrameOffSet);

	myHealthBar->SetPosition(aPlayerPosition + myDistanceFromPlayer - myHealthBarOffSet);
	myPowerUpBar->SetPosition(aPlayerPosition + myDistanceFromPlayer + myPowerupFrameOffSet - myPowerupBarOffSet);
}

void HealthBar::OnEvent(int someNewHealth)
{
	const float percentange = MathHelper::Clamp(someNewHealth / static_cast<float>(myHealthInterface->GetMaxHealth()), 0.0f, 1.0f);

	const CU::Vector2<float> newSize = { myInitialHealthBarWidth * percentange, myHealthBar->GetSize().y };

	myHealthBar->SetTextureRect({ 0.0f, 0.0f, percentange, 1.0f });
	myHealthBar->SetSize(newSize);
}
