#include "stdafx.h"
#include "PowerUp.h"
#include "JsonManager.h"
#include "SpriteSheetAnimation.h"
#include "GlobalServiceProvider.h"
#include "Player.h"

PowerUp::PowerUp(Scene* aScene, PowerUpType aPowerUpType)
	: Collectable(aScene)
	, myPowerUpType(aPowerUpType)
{
	if (aPowerUpType == PowerUpType::Berserk)
	{
		InitWithJson(GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/Entities.json").at("BerserkerPickup"));
	}
}

void PowerUp::InitWithJson(const JsonData& someProperties)
{
	Init();
	
	mySprite = std::make_shared<SpriteWrapper>();
	myAnimation = std::make_unique<SpriteSheetAnimation>(myScene->GetGlobalServiceProvider()->GetJsonManager(), someProperties.at("SpritePath"));

	myAnimation->SetState("idle");
	myAnimation->SetIsLooping(true);

	myAnimation->ApplyToSprite(mySprite);
	SetTriggerSize(mySprite->GetSize());
}

void PowerUp::OnCollect(Player* aPlayer)
{
	aPlayer->ActivatePowerUp(myPowerUpType);
}
