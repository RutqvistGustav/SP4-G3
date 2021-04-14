#include "stdafx.h"
#include "MenuScene.h"

#include "CollisionManager.h"

#include "Metrics.h"

#include "MousePointer.h"

#include "Camera.h"

#include "UpdateContext.h"

#include "InputManager.h"

MenuScene::MenuScene() = default;

MenuScene::~MenuScene() = default;

void MenuScene::Init()
{
	myCollisionManager = std::make_unique<CollisionManager>();

	myMousePointer = std::make_unique<MousePointer>(this);
	myMousePointer->Init();

	GetCamera()->SetLevelBounds(AABB({ 0.0f, 0.0f }, Metrics::GetReferenceSize()));
	GetCamera()->SetPosition(Metrics::GetReferenceSize() * 0.5f);
}

void MenuScene::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	Scene::Update(aDeltaTime, anUpdateContext);

	myMousePointer->Update(aDeltaTime, anUpdateContext);
	
	ControllerNavigate(anUpdateContext);
	ControllerControl(aDeltaTime, anUpdateContext);
	
	if (anUpdateContext.myInputInterface->IsJumping())
	{
		MouseClicked(myGameObjects[myCurrentButtonIndex].get());
	}
	myMousePointer->SetPosition(myGameObjects[myCurrentButtonIndex]->GetPosition());

	myCollisionManager->Update();
}

void MenuScene::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	Scene::Render(aRenderQueue, aRenderContext);

	myMousePointer->Render(aRenderQueue, aRenderContext);
}

void MenuScene::ControllerControl(const float aDeltaTime, UpdateContext& /*anUpdateContext*/)
{

	if (myCurrentButtonIndex < 0)
	{
		myCurrentButtonIndex = myGameObjects.size() - 1;
	}
	else if (myCurrentButtonIndex > myGameObjects.size() - 1)
	{
		myCurrentButtonIndex = 0;
	}
	

}

void MenuScene::AddInterfaceElement(std::shared_ptr<GameObject> anElement)
{
	AddGameObject(anElement);
}

const bool MenuScene::CheckNext(UpdateContext& anUpdateContext) const
{
	return anUpdateContext.myInputInterface->GetLeftStickY() > 0.0001;
}

const bool MenuScene::CheckPrev(UpdateContext& anUpdateContext) const
{
	return anUpdateContext.myInputInterface->GetLeftStickY() < -0.0001;
}

void MenuScene::ControllerNavigate(UpdateContext& anUpdateContext)
{
	if (CheckNext(anUpdateContext) && mySwitchingButton == false)
	{
		--myCurrentButtonIndex;
		mySwitchingButton = true;
	}
	else if (CheckPrev(anUpdateContext) && mySwitchingButton == false)
	{
		++myCurrentButtonIndex;
		mySwitchingButton = true;
	}
	else if (!CheckNext(anUpdateContext) && !CheckPrev(anUpdateContext))
	{
		mySwitchingButton = false;
	}
}
