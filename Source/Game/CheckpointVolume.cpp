#include "stdafx.h"
#include "CheckpointVolume.h"
#include "SpriteSheetAnimation.h"

#include "LevelManagerProxy.h"
#include "GlobalServiceProvider.h"

#include <cassert>

CheckpointVolume::CheckpointVolume(Scene* aScene) :
	TriggerVolume(aScene, GameObjectTag::Player)
{}

void CheckpointVolume::Init()
{
	CU::Vector2<float> triggerSize = GetTriggerSize();
	GameObject::Init();
	SetTriggerSize(triggerSize);
	mySprite->SetPosition({mySprite->GetPosition().x, mySprite->GetPosition().y + (GetTriggerSize().y * 0.5f)});
	mySprite->SetPivot({ 0.5f, 1.0f });
	myAnimation = std::make_unique<SpriteSheetAnimation>(myScene->GetGlobalServiceProvider()->GetJsonManager(), "Animations/CheckPoint.json");
	myAnimation->SetIsLooping(true);
	myAnimation->SetState("preTrigger");
}

void CheckpointVolume::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	if (myIsUsed && myAnimation->HasEnded())
	{
		myAnimation->SetState("postTriggered");
		myAnimation->SetIsLooping(true);
	}
	myAnimation->Update(aDeltaTime);
	myAnimation->ApplyToSprite(mySprite);
}

void CheckpointVolume::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	GameObject::Render(aRenderQueue, aRenderContext);
}

void CheckpointVolume::TriggerEnter(GameObject* /*aGameObject*/)
{
	if (!myIsUsed)
	{
 		myScene->GetLevelManagerProxy()->SaveCheckpoint();
		myAnimation->SetState("triggered");
		myAnimation->SetIsLooping(false);
		myIsUsed = true;
	}
}
