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
#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"

MainMenu::MainMenu() = default;
MainMenu::~MainMenu() = default;

void MainMenu::Init()
{
	myTiledParser = std::make_unique<TiledParser>("Maps/EmptyMap.json");
	myTiledRenderer = std::make_unique<TiledRenderer>(myTiledParser.get());
	myTiledCollision = std::make_unique<TiledCollision>(myTiledParser.get());
	myCollisionManager = std::make_unique<CollisionManager>(myTiledCollision.get());

	myBackground = std::make_shared<SpriteWrapper>("Sprites/Menue UI/menu_background.png");
	myBackground->SetPanStrengthFactor(0);

	myMousePointer = std::make_unique<MousePointer>(this);
	InitButtons();
}

void MainMenu::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myCollisionManager->Update();

	float x = Metrics::GetReferenceSize().x;
	float y = Metrics::GetReferenceSize().y;

	myBackground->SetPosition(CU::Vector2(x / 2, y / 2));

	for (auto& o : myButtons)
	{
		o->Update();
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
		//case GameObjectTag::SettingsButton:
		//{
		//	GetSceneManagerProxy()->Transition(std::make_unique<Options>());
		//	break;
		//}
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

	myStartButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/start.dds", "Sprites/Menue UI/start_hover.dds", GameObjectTag::StartButton);
	myStartButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.33f));
	myButtons.push_back(std::move(myStartButton));

	myLevelSelectButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/levels.dds", "Sprites/Menue UI/levels_hover.dds", GameObjectTag::LevelSelectButton);
	myLevelSelectButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.43f));
	myButtons.push_back(std::move(myLevelSelectButton));

	mySettingsButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/settings.dds", "Sprites/Menue UI/settings_hover.dds", GameObjectTag::SettingsButton);
	mySettingsButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.53f));
	myButtons.push_back(std::move(mySettingsButton));

	myCreditsButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/credits.dds", "Sprites/Menue UI/credits_hover.dds", GameObjectTag::CreditsButton);
	myCreditsButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.63f));
	myButtons.push_back(std::move(myCreditsButton));

	myQuitButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/quit.dds", "Sprites/Menue UI/quit_hover.dds", GameObjectTag::QuitButton);
	myQuitButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.73f));
	myButtons.push_back(std::move(myQuitButton));
}
