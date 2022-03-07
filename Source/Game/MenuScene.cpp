#include "stdafx.h"
#include "MenuScene.h"

#include "CollisionManager.h"

#include "Metrics.h"

#include "MousePointer.h"

#include "Camera.h"

#include "UpdateContext.h"

#include "InputManager.h"
#include "GlobalServiceProvider.h"
#include "GameMessenger.h"
#include "IndexMessageData.h"

MenuScene::MenuScene() = default;

MenuScene::~MenuScene()
{
	GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::CurrentButton, this);
}

void MenuScene::Init()
{
	myCollisionManager = std::make_unique<CollisionManager>();

	myMousePointer = std::make_unique<MousePointer>(this);
	myMousePointer->Init();

	GetCamera()->SetLevelBounds(AABB({ 0.0f, 0.0f }, Metrics::GetReferenceSize()));
	GetCamera()->SetPosition(Metrics::GetReferenceSize() * 0.5f);

	GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::CurrentButton, this);
}

void MenuScene::Update(const float aDeltaTime, UpdateContext & anUpdateContext)
{
	Scene::Update(aDeltaTime, anUpdateContext);

	//myMousePointer->Update(aDeltaTime, anUpdateContext);

	/*if (anUpdateContext.myInputInterface->IsUsingController())
	{*/
	ControllerNavigate(anUpdateContext);
	ControllerControl(aDeltaTime, anUpdateContext);

	if (anUpdateContext.myInputInterface->IsJumping())
	{
		MouseClicked(myGameObjects[myCurrentButtonIndex].get());
	}
	else if (anUpdateContext.myInputInterface->BackButton())
	{
		assert(myBackButtonIndex != -1 && "myBackButtonIndex is not assigned");
		MouseClicked(myGameObjects[myBackButtonIndex].get());
	}

	myMousePointer->SetPosition(myGameObjects[myCurrentButtonIndex]->GetPosition());
	//}

	myCollisionManager->Update();

	if (myButtonClicked)
	{
		MouseClicked(myGameObjects[myButtonIndexClicked].get());
		myButtonClicked = false;
	}
}

void MenuScene::Render(RenderQueue* const aRenderQueue, RenderContext & aRenderContext)
{
	Scene::Render(aRenderQueue, aRenderContext);

	myMousePointer->Render(aRenderQueue, aRenderContext);

#ifndef _RETAIL
	if (myCollisionManager->GetShowColliders())
	{
		myCollisionManager->RenderDebug(aRenderQueue, aRenderContext);
	}
#endif // !_RETAIL

}

void MenuScene::ControllerControl(const float /*aDeltaTime*/, UpdateContext& /*anUpdateContext*/)
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

const bool MenuScene::CheckNext(UpdateContext & anUpdateContext) const
{
	return anUpdateContext.myInputInterface->GetLeftStickY() > 0.0001;
		//|| anUpdateContext.myInput->IsKeyDown('W');
}

const bool MenuScene::CheckPrev(UpdateContext & anUpdateContext) const
{
	return anUpdateContext.myInputInterface->GetLeftStickY() < -0.0001;
		//|| anUpdateContext.myInput->IsKeyDown('S');
}

void MenuScene::ControllerNavigate(UpdateContext & anUpdateContext)
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

GameMessageAction MenuScene::OnMessage(const GameMessage aMessage, const void* someMessageData)
{
	if (aMessage == GameMessage::CurrentButton)
	{
		auto message = reinterpret_cast<const IndexMessageData*>(someMessageData);
		int nextIndex = message->myIndex;
		nextIndex += myCurrentButtonIndex;

		myCurrentButtonIndex = nextIndex;
		return GameMessageAction::Keep;
	}
	if (aMessage == GameMessage::ButtonClicked)
	{
		myButtonClicked = true;
		myButtonIndexClicked = myCurrentButtonIndex;
		return GameMessageAction::Unsubscribe;
	}

	return GameMessageAction::Keep;
}