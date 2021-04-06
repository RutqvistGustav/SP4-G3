#include "stdafx.h"
#include "PauseMenu.h"
#include "MenuButton.h"
#include "SpriteWrapper.h"
#include "SceneManagerProxy.h"

#include "MainMenu.h"

#include "RenderQueue.h"
#include "RenderCommand.h"
#include "MousePointer.h"
#include "Metrics.h"

#include "TiledCollision.h"
#include "TiledRenderer.h"
#include "TiledParser.h"

PauseMenu::PauseMenu() = default;
PauseMenu::~PauseMenu() = default;

void PauseMenu::Init()
{
	//myTiledParser = std::make_unique<TiledParser>("Maps/EmptyMap.json");
	//myTiledRenderer = std::make_unique<TiledRenderer>(myTiledParser.get());
	//myTiledCollision = std::make_unique<TiledCollision>(myTiledParser.get());
	//myCollisionManager = std::make_unique<CollisionManager>(myTiledCollision.get());
	//
	//myMousePointer = std::make_unique<MousePointer>(this);
	//
	//myBackGround = std::make_shared<SpriteWrapper>("");
	//myBackGround->SetPanStrengthFactor(0);

	//InitButtons();
}

void PauseMenu::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	//myCollisionManager->Update();
	//
	//float x = Metrics::GetReferenceSize().x;
	//float y = Metrics::GetReferenceSize().y;
	//
	//myBackGround->SetPosition(CU::Vector2(x / 2, y / 2));
	//
	//for (auto& button : myButtons)
	//{
	//	button->Update();
	//}
	//
	//myMousePointer->Update(aDeltaTime, anUpdateContext);
	//
	//if (myMousePointer->ButtonClicked())
	//{
	//	switch (myMousePointer->ClickedButton())
	//	{
	//	case GameObjectTag::StartButton:
	//	{
	//		
	//		break;
	//	}
	//	case GameObjectTag::QuitButton:
	//	{
	//		GetSceneManagerProxy()->Transition(std::make_unique<MainMenu>());
	//		break;
	//	}
	//	}
	//}
}

void PauseMenu::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	//aRenderQueue->Queue(RenderCommand(myBackGround));
	//
	//for (auto& button : myButtons)
	//{
	//	button->Render(aRenderQueue, aRenderContext);
	//}
}

void PauseMenu::InitButtons()
{
	//float x = Metrics::GetReferenceSize().x;
	//float y = Metrics::GetReferenceSize().y;
	//
	//myStartButton = std::make_unique<MenuButton>(this, "Sprite 1", "Sprite 2", GameObjectTag::StartButton);
	//myStartButton->SetPosition(CU::Vector2(x / 2, y /* * insert y offset*/));
	//myButtons.push_back(myStartButton);
	//
	//myQuitButton = std::make_unique<MenuButton>(this, "Sprite 1", "Sprite 2", GameObjectTag::QuitButton);
	//myQuitButton->SetPosition(CU::Vector2(x / 2, y /* * insert y offset*/));
	//myButtons.push_back(myQuitButton);
}
