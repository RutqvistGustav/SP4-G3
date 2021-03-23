#include "stdafx.h"
#include "Collectable.h"

#include "GameObjectTag.h"

#include "Player.h"
#include "Scene.h"

#include "GlobalServiceProvider.h"

#include "SpriteSheetAnimation.h"
#include "SpriteWrapper.h"

Collectable::Collectable(Scene* aScene) :
	TriggerVolume(aScene, GameObjectTag::Player)
{}

Collectable::~Collectable() = default;

void Collectable::InitWithJson(const JsonData& /*someProperties*/)
{
	Init();

	// TODO: Find sprite from and configure animation from json

	myAnimation = std::make_unique<SpriteSheetAnimation>(GetScene()->GetGlobalServiceProvider()->GetJsonManager(), "Animations/TestAnimation.json");

	myAnimation->SetState("default");
	myAnimation->SetIsLooping(true);

	myAnimation->ApplyToSprite(mySprite);
	SetTriggerRadius(mySprite->GetSize().x * 0.5f);
}

void Collectable::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	TriggerVolume::Update(aDeltaTime, anUpdateContext);

	myAnimation->Update(aDeltaTime);
	myAnimation->ApplyToSprite(mySprite);
}

void Collectable::OnStay(GameObject * aGameObject)
{
	Player* player = static_cast<Player*>(aGameObject);

	if (CanCollect(player))
	{
		OnCollect(player);

		myIsCollected = true;
		// TODO: Mark GameObject for destruction
	}
}

bool Collectable::CanCollect(Player* aPlayer)
{
	return !myIsCollected;
}
