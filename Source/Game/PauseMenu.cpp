#include "stdafx.h"
#include "PauseMenu.h"
#include "MenuButton.h"
#include "SpriteWrapper.h"
#include "SceneManagerProxy.h"
#include "UpdateContext.h"
#include "LevelManagerProxy.h"

#include "MainMenu.h"

#include "RenderQueue.h"
#include "RenderCommand.h"
#include "MousePointer.h"
#include "Metrics.h"
#include "CollisionManager.h"

PauseMenu::PauseMenu() = default;
PauseMenu::~PauseMenu() = default;

void PauseMenu::Init()
{
	MenuScene::Init();

	myBackGround = std::make_shared<SpriteWrapper>("Sprites/Menue UI/pause/pause background.dds");
	myBackGround->SetPosition(Metrics::GetReferenceSize() * 0.5f);
	myBackGround->SetLayer(100);
	myBackGround->SetPanStrengthFactor(0);

	InitButtons();

	myMousePointer->SetClickCallback(std::bind(&PauseMenu::MouseClicked, this, std::placeholders::_1)); // TODO What does this do?
}

void PauseMenu::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	MenuScene::Update(aDeltaTime, anUpdateContext);

	if (anUpdateContext.myInputInterface->IsPressingPause())
	{
		if (!myPauseIsActive)
		{
			myPauseIsActive = true;
		}
		else
		{
			myPauseIsActive = false;
		}
	}
}

void PauseMenu::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	MenuScene::Render(aRenderQueue, aRenderContext);
	aRenderQueue->Queue(RenderCommand(myBackGround));
}

const bool PauseMenu::IsGamePaused()
{
	return myPauseIsActive;
}

void PauseMenu::InitButtons()
{
	float width = Metrics::GetReferenceSize().x;
	float height = Metrics::GetReferenceSize().y;
	
	auto startButton = std::make_shared<MenuButton>(this, "Sprites/Menue UI/pause/continue.dds", "Sprites/Menue UI/pause/continue_hover.dds",
		GameObjectTag::StartButton);
	startButton->SetPosition(CU::Vector2(width * 0.5f, height * 0.43f));
	startButton->SetLayer(103);
	startButton->SetPanStrengthFactor(0);
	AddGameObject(startButton);

	auto restartButton = std::make_shared<MenuButton>(this, "Sprites/Menue UI/pause/restart.dds", "Sprites/Menue UI/pause/restart_hover.dds",
		GameObjectTag::RestartButton);
	restartButton->SetPosition(CU::Vector2(width * 0.5f, height * 0.53f));
	restartButton->SetLayer(103);
	restartButton->SetPanStrengthFactor(0);
	AddGameObject(restartButton);
	
	auto quitButton = std::make_shared<MenuButton>(this, "Sprites/Menue UI/pause/main menu.dds", "Sprites/Menue UI/pause/main menu_hover.dds",
		GameObjectTag::QuitButton);
	quitButton->SetPosition(CU::Vector2(width * 0.5f, height * 0.63f));
	quitButton->SetLayer(103);
	quitButton->SetPanStrengthFactor(0);
	AddGameObject(quitButton);
}

void PauseMenu::MouseClicked(GameObject* aTarget)
{
	if (aTarget == nullptr) return;

	const GameObjectTag targetTag = aTarget->GetTag();

	switch (targetTag)
	{
	case GameObjectTag::StartButton:
		myPauseIsActive = false;
		break;

	case GameObjectTag::RestartButton:
		GetLevelManagerProxy()->RestartCurrentLevel();
		break;

	case GameObjectTag::QuitButton:
		//GetSceneManagerProxy()->Transition(std::make_unique<MainMenu>());
		GetSceneManagerProxy()->TransitionToMainMenu();
		break;
	}
	
}
