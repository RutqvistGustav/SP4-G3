#include "stdafx.h"
#include "MainMenu.h"
#include "Metrics.h"
#include "MousePointer.h"
#include "SceneManagerProxy.h"
#include "GameScene.h"
#include "MenuButton.h"
#include "CollisionManager.h"
#include "Options.h"
#include "TiledParser.h"
#include "TiledRenderer.h"
#include "TiledCollision.h"

MainMenu::MainMenu() = default;
MainMenu::~MainMenu() = default;

void MainMenu::Init()
{
	myTiledParser = std::make_unique<TiledParser>("Maps/EmptyMap.json");
	myTiledRenderer = std::make_unique<TiledRenderer>(myTiledParser.get());
	myTiledCollision = std::make_unique<TiledCollision>(myTiledParser.get());
	myCollisionManager = std::make_unique<CollisionManager>(myTiledCollision.get());

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
		case GameObjectTag::SettingsButton:
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

	myStartButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/start.dds", GameObjectTag::StartButton);
	myStartButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.3f));
	myButtons.push_back(std::move(myStartButton));

	myLevelSelectButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/levels.dds", GameObjectTag::LevelSelectButton);
	myLevelSelectButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.4f));
	myButtons.push_back(std::move(myLevelSelectButton));

	mySettingsButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/settings.dds", GameObjectTag::SettingsButton);
	mySettingsButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.5f));
	myButtons.push_back(std::move(mySettingsButton));

	myCreditsButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/credits.dds", GameObjectTag::CreditsButton);
	myCreditsButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.6f));
	myButtons.push_back(std::move(myCreditsButton));

	myQuitButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/quit.dds", GameObjectTag::QuitButton);
	myQuitButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.7f));
	myButtons.push_back(std::move(myQuitButton));
}
