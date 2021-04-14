#include "stdafx.h"
#include "Key.h"
#include "GlobalServiceProvider.h"
#include "JsonManager.h"
#include "LevelManagerProxy.h"

#include "DialogueBox.h"
#include "SpriteSheetAnimation.h"

// TODO: REMOVE
#include <iostream>

Key::Key(Scene* aScene, PowerUpType aPowerupType)
	: Collectable(aScene)
{
	InitWithJson(GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/Entities.json").at("Key"));
}

void Key::InitWithJson(const JsonData& someProperties)
{
	Init();

	myDialogBox = std::make_unique<DialogueBox>(GetScene(), true);
	myDialogBox->Init(stringID);

	mySprite = std::make_shared<SpriteWrapper>();
	myAnimation = std::make_unique<SpriteSheetAnimation>(myScene->GetGlobalServiceProvider()->GetJsonManager(), "Animation/TestAnimation.json");

	myAnimation->SetState("idle");
	myAnimation->SetIsLooping(true);

	myAnimation->ApplyToSprite(mySprite);
	SetTriggerSize(mySprite->GetSize());
}

void Key::OnCollect(Player* /*aPlayer*/)
{
	// TODO Activate dialogue box
}

void Key::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	TriggerVolume::Update(aDeltaTime, anUpdateContext);

	myDialogBox->Update(aDeltaTime, anUpdateContext);

	myAnimation->Update(aDeltaTime);
	myAnimation->ApplyToSprite(mySprite);

	if (myDialogBox->GetDeleteThisFrame() == true) 
	{
		GetScene()->GetLevelManagerProxy()->TransitionNextLevel();
	}
}

void Key::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	GameObject::Render(aRenderQueue, aRenderContext);
	myDialogBox->Render(aRenderQueue, aRenderContext);
}
