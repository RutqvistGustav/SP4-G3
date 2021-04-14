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
	
	ControllerControl(anUpdateContext);
	
	myCollisionManager->Update();
}

void MenuScene::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	Scene::Render(aRenderQueue, aRenderContext);

	myMousePointer->Render(aRenderQueue, aRenderContext);
}

void MenuScene::ControllerControl(UpdateContext& anUpdateContext)
{


	if (anUpdateContext.myInputInterface->GetLeftStickY() > 0.0001 && mySwitchingButton == false)
	{
		--myCurrentButtonIndex;
		mySwitchingButton = true;
	}
	else if (anUpdateContext.myInputInterface->GetLeftStickY() < -0.0001 && mySwitchingButton == false)
	{
		++myCurrentButtonIndex;
		mySwitchingButton = true;
	}
	else if (!(anUpdateContext.myInputInterface->GetLeftStickY() > 0.0001) 
		&& !(anUpdateContext.myInputInterface->GetLeftStickY() < -0.0001))
	{
		mySwitchingButton = false;
	}

	if (myCurrentButtonIndex < 0)
	{
		myCurrentButtonIndex = myGameObjects.size() - 1;
	}
	else if (myCurrentButtonIndex > myGameObjects.size() - 1)
	{
		myCurrentButtonIndex = 0;
	}
	myMousePointer->SetPosition(myGameObjects[myCurrentButtonIndex]->GetPosition());

	if (anUpdateContext.myInputInterface->IsJumping())
	{
		MouseClicked(myGameObjects[myCurrentButtonIndex].get());
	}


}

void MenuScene::AddInterfaceElement(std::shared_ptr<GameObject> anElement)
{
	AddGameObject(anElement);
}
