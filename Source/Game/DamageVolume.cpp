#include "stdafx.h"
#include "DamageVolume.h"

#include "GlobalServiceProvider.h"
#include "SpriteSheetAnimation.h"
#include "SpriteWrapper.h"

#include "Scene.h"
#include "Player.h"

DamageVolume::DamageVolume(Scene* aScene) :
	TriggerVolume(aScene, GameObjectTag::Player)
{}

void DamageVolume::InitWithJson(const JsonData & someProperties)
{
	Init();

	// TODO: Load in from json
	myDamage = 1;
	myKnockbackStrength = 1000.0f;

	myAnimation = std::make_unique<SpriteSheetAnimation>(GetScene()->GetGlobalServiceProvider()->GetJsonManager(), "Animations/TestAnimation.json");

	myAnimation->SetState("default");
	myAnimation->SetIsLooping(true);

	myAnimation->ApplyToSprite(mySprite);
	SetTriggerSize(mySprite->GetSize());
}

void DamageVolume::TriggerStay(GameObject* aGameObject)
{
	Player* player = static_cast<Player*>(aGameObject);

	Damage(player);
}

void DamageVolume::Damage(Player* aPlayer)
{
	aPlayer->TakeDamage(myDamage);
	aPlayer->ApplyForce((aPlayer->GetPosition() - GetPosition()).GetNormalized() * myKnockbackStrength);
}
