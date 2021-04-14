#include "stdafx.h"
#include "HealthPickup.h"
#include "Collectable.h"
#include "Player.h"
#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "AudioManager.h"
#include "SpriteSheetAnimation.h"
#include "SpriteWrapper.h"
#include "JsonManager.h"

HealthPickup::HealthPickup(Scene* aScene, PowerUpType aPowerupType)
	: Collectable(aScene, aPowerupType)
{
	InitWithJson(GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/Entities.json").at("HealthPickup"));
}

void HealthPickup::InitWithJson(const JsonData& someProperties)
{
	Init();

	mySprite = std::make_shared<SpriteWrapper>();
	mySprite->SetLayer(GameLayer::Prop);

	myAnimation = std::make_unique<SpriteSheetAnimation>(myScene->GetGlobalServiceProvider()->GetJsonManager(), someProperties.at("SpritePath"));

	myAnimation->SetState("idle");
	myAnimation->SetIsLooping(true);

	myAnimation->ApplyToSprite(mySprite);
	SetTriggerSize(mySprite->GetSize());

	myHealingValue = someProperties.value("Health", 1);
}

void HealthPickup::OnCollect(Player* aPlayer)
{
	aPlayer->AddHealth(myHealingValue);
	GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Misc/Health_Pickup.wav");
}
