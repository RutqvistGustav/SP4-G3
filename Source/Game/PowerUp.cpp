#include "stdafx.h"
#include "PowerUp.h"
#include "JsonManager.h"
#include "SpriteSheetAnimation.h"
#include "SpriteWrapper.h"
#include "GlobalServiceProvider.h"
#include "AudioManager.h"
#include "Player.h"

PowerUp::PowerUp(Scene* aScene, PowerUpType aPowerUpType)
	: Collectable(aScene, aPowerUpType)
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
	mySprite->SetLayer(GameLayer::Prop);

	myAnimation = std::make_unique<SpriteSheetAnimation>(myScene->GetGlobalServiceProvider()->GetJsonManager(), someProperties.at("SpritePath"));

	myAnimation->SetState("idle");
	myAnimation->SetIsLooping(true);

	myAnimation->ApplyToSprite(mySprite);
	SetTriggerSize(mySprite->GetSize());
}

void PowerUp::OnCollect(Player* aPlayer)
{
	aPlayer->ActivatePowerUp(myPowerupType);
	GetScene()->GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Misc/Berserk powerup.mp3");
}
