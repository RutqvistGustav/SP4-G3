#include "stdafx.h"
#include "MainMenu.h"
#include "Metrics.h"
#include "MousePointer.h"
#include "SceneManagerProxy.h"
#include "GameScene.h"
#include "MenuButton.h"
#include "CollisionManager.h"
#include "Settings.h"
#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"
#include "TiledParser.h"
#include "TiledRenderer.h"
#include "TiledCollision.h"
#include "LevelSelect.h"

MainMenu::MainMenu() = default;
MainMenu::~MainMenu() = default;

void MainMenu::Init()
{
	myTiledParser = std::make_unique<TiledParser>("Maps/EmptyMap.json");
	myTiledRenderer = std::make_unique<TiledRenderer>(myTiledParser.get());
	myTiledCollision = std::make_unique<TiledCollision>(myTiledParser.get());
	myCollisionManager = std::make_unique<CollisionManager>(myTiledCollision.get());

	myBackground = std::make_shared<SpriteWrapper>("Sprites/Menue UI/menu background.dds");
	myBackground->SetPanStrengthFactor(0);

	myMousePointer = std::make_unique<MousePointer>(this);
	InitButtons();
}

void MainMenu::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myCollisionManager->Update();

	float x = Metrics::GetReferenceSize().x;
	float y = Metrics::GetReferenceSize().y;

	myBackground->SetPosition(CU::Vector2(x * 0.5f, y * 0.5f));

	for (auto& o : myButtons)
	{
		o->Update();
	}

	myMousePointer->Update(aDeltaTime, anUpdateContext);

	if (myMousePointer->GetButtonClicked())
	{
		switch (myMousePointer->ClickedButton())
		{
		case GameObjectTag::StartButton:
		{
			GetSceneManagerProxy()->Transition(std::make_unique<GameScene>("Maps/Level1.json"));
			break;
		}
		case GameObjectTag::SettingsButton:
		{
			GetSceneManagerProxy()->Transition(std::make_unique<Settings>());
			break;
		}
		case GameObjectTag::LevelSelectButton:
		{
			GetSceneManagerProxy()->Transition(std::make_unique<LevelSelect>());
			break;
		}
		case GameObjectTag::QuitButton:
		{
			PostQuitMessage(0);
			break;
		}
		}
		myMousePointer->SetButtonClicked(false);
	}
}

void MainMenu::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	RenderCommand renderCommand = RenderCommand(myBackground);
	aRenderQueue->Queue(renderCommand);

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

	myStartButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/start.dds", "Sprites/Menue UI/start_hover.dds", 
		GameObjectTag::StartButton);
	myStartButton->SetPosition(CommonUtilities::Vector2(x * 0.5f, y * 0.33f));
	myButtons.push_back(std::move(myStartButton));

	myLevelSelectButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/levels.dds", "Sprites/Menue UI/levels_hover.dds",
		GameObjectTag::LevelSelectButton);
	myLevelSelectButton->SetPosition(CommonUtilities::Vector2(x * 0.5f, y * 0.43f));
	myButtons.push_back(std::move(myLevelSelectButton));

	mySettingsButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/settings.dds", "Sprites/Menue UI/settings_hover.dds", 
		GameObjectTag::SettingsButton);
	mySettingsButton->SetPosition(CommonUtilities::Vector2(x * 0.5f, y * 0.53f));
	myButtons.push_back(std::move(mySettingsButton));

	myCreditsButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/credits.dds", "Sprites/Menue UI/credits_hover.dds", 
		GameObjectTag::CreditsButton);
	myCreditsButton->SetPosition(CommonUtilities::Vector2(x * 0.5f, y * 0.63f));
	myButtons.push_back(std::move(myCreditsButton));

	myQuitButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/quit.dds", "Sprites/Menue UI/quit_hover.dds", 
		GameObjectTag::QuitButton);
	myQuitButton->SetPosition(CommonUtilities::Vector2(x * 0.5f, y * 0.73f));
	myButtons.push_back(std::move(myQuitButton));
}
