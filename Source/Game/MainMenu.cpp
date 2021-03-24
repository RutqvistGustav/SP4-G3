#include "stdafx.h"
#include "MainMenu.h"
#include "Metrics.h"
#include "MousePointer.h"
#include "SceneManagerProxy.h"
#include "GameScene.h"
#include "MenuButton.h"
#include "CollisionManager.h"
#include "Options.h"

MainMenu::MainMenu() = default;
MainMenu::~MainMenu() = default;

void MainMenu::Init()
{
	myCollisionManager = std::make_unique<CollisionManager>();
	myMousePointer = std::make_unique<MousePointer>(this);
	InitButtons();
}

void MainMenu::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myCollisionManager->Update();

	for (auto& o : myButtons)
	{
		o->Update(aDeltaTime, anUpdateContext);
	}

	myMousePointer->Update(aDeltaTime, anUpdateContext);

	if (myMousePointer->ButtonClicked())
	{
		switch (myMousePointer->ClickedButton())
		{
		case GameObjectTag::StartButton:
		{
			GetSceneManagerProxy()->Transition(std::make_unique<GameScene>());
			break;
		}
		case GameObjectTag::OptionsButton:
		{
			GetSceneManagerProxy()->Transition(std::make_unique<Options>());
			break;
		}
		case GameObjectTag::QuitButton:
		{
			PostMessage(*Tga2D::CEngine::GetInstance()->GetHWND(), WM_USER + 0, 0, 0);
			break;
		}
		}
	}
}

void MainMenu::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	for (auto& o : myButtons)
	{
		o->Render(aRenderQueue, aRenderContext);
	}

	myMousePointer->Render(aRenderQueue, aRenderContext);
}

void MainMenu::InitButtons()
{
	float x = Metrics::GetReferenceSize().x;
	float y = Metrics::GetReferenceSize().y;

	myStartButton = std::make_unique<MenuButton>(this, "Sprites/StartButton.png", GameObjectTag::StartButton);
	myStartButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.10f));
	myButtons.push_back(std::move(myStartButton));

	myOptionsButton = std::make_unique<MenuButton>(this, "Sprites/OptionsButton.png", GameObjectTag::OptionsButton);
	myOptionsButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.50f));
	myButtons.push_back(std::move(myOptionsButton));

	myQuitButton = std::make_unique<MenuButton>(this, "Sprites/QuitButton.png", GameObjectTag::QuitButton);
	myQuitButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.90f));
	myButtons.push_back(std::move(myQuitButton));

	myLevelSelectButton = std::make_unique<MenuButton>(this, "Sprites/LevelSelectButton.png", GameObjectTag::LevelSelectButton);
	myLevelSelectButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.90f));
	myButtons.push_back(std::move(myLevelSelectButton));
}
