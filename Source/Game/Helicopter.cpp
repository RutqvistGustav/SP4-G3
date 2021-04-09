#include "stdafx.h"
#include "Helicopter.h"

#include "GlobalServiceProvider.h"
#include "Scene.h"

#include "SpriteSheetAnimation.h"

Helicopter::Helicopter(Scene* aScene) :
	GameObject(aScene)
{
	myAnimation = std::make_unique<SpriteSheetAnimation>(aScene->GetGlobalServiceProvider()->GetJsonManager(), "Animations/Helicopter.json");
}

void Helicopter::Init()
{
	myCollider.reset();
	GameObject::Init();

	mySprite->SetLayer(GameLayer::Prop);

	myAnimation->SetState("default");
	myAnimation->SetIsLooping(true);

	myAnimation->ApplyToSprite(mySprite);
}

void Helicopter::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myAnimation->Update(aDeltaTime);
	myAnimation->ApplyToSprite(mySprite);
}
