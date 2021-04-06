#include "stdafx.h"
#include "HealthPickup.h"
#include "Collectable.h"
#include "Player.h"
#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "SpriteSheetAnimation.h"
#include "JsonManager.h"

HealthPickup::HealthPickup(Scene* aScene)
	: Collectable(aScene)
{
	myHealingValue = 1;

	InitWithJson(GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/Entities.json").at("HealthPickup"));
}

void HealthPickup::InitWithJson(const JsonData& someProperties)
{
	Init();

	mySprite = std::make_shared<SpriteWrapper>();
	myAnimation = std::make_unique<SpriteSheetAnimation>(myScene->GetGlobalServiceProvider()->GetJsonManager(), someProperties.at("SpritePath"));

	myAnimation->SetState("idle");
	myAnimation->SetIsLooping(true);

	myAnimation->ApplyToSprite(mySprite);
	SetTriggerSize(mySprite->GetSize());
}

void HealthPickup::OnCollect(Player* aPlayer)
{
	aPlayer->AddHealth(myHealingValue);
}
