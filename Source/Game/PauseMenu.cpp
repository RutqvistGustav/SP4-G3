#include "stdafx.h"
#include "PauseMenu.h"
#include "MenuButton.h"
#include "SpriteWrapper.h"
#include "SceneManagerProxy.h"
#include "UpdateContext.h"
#include "LevelManagerProxy.h"

#include "GlobalServiceProvider.h"
#include "AudioManager.h"

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

	myBackGround = std::make_shared<SpriteWrapper>();
	myBackGround->SetPosition(Metrics::GetReferenceSize() * 0.5f);
	myBackGround->SetSize(Metrics::GetReferenceSize());
	myBackGround->SetColor(Tga2D::CColor(0.0f, 0.0f, 0.0f, 0.36f));
	myBackGround->SetLayer(99);
	myBackGround->SetPanStrengthFactor(0);
	myBackGround->SetSamplerFilter(RenderSamplerFilter::Bilinear);

	InitButtons();

	myMousePointer->SetClickCallback(std::bind(&PauseMenu::MouseClicked, this, std::placeholders::_1)); // TODO What does this do?
}

void PauseMenu::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	if (mySettings == nullptr)
	{
		MenuScene::Update(aDeltaTime, anUpdateContext);
		Input(anUpdateContext);
	}
	else
	{
		mySettings->Update(aDeltaTime, anUpdateContext);
		if (mySettings->IsSettingsActive() == false)
		{
			mySettings.reset();
		}
	}
}

void PauseMenu::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	aRenderQueue->Queue(RenderCommand(myBackGround));
	if (mySettings == nullptr)
	{
		MenuScene::Render(aRenderQueue, aRenderContext);
	}
	else
	{
		mySettings->Render(aRenderQueue, aRenderContext);
	}
}

void PauseMenu::Input(UpdateContext& anUpdateContext)
{
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
	startButton->SetPosition(CU::Vector2(width * 0.5f, height * 0.33f));
	startButton->SetLayer(100);
	startButton->SetPanStrengthFactor(0);
	AddGameObject(startButton);

	auto restartButton = std::make_shared<MenuButton>(this, "Sprites/Menue UI/pause/restart.dds", "Sprites/Menue UI/pause/restart_hover.dds",
		GameObjectTag::RestartButton);
	restartButton->SetPosition(CU::Vector2(width * 0.5f, height * 0.43f));
	restartButton->SetLayer(100);
	restartButton->SetPanStrengthFactor(0);
	AddGameObject(restartButton);

	auto settingsButton = std::make_shared<MenuButton>(this, "Sprites/Menue UI/settings.dds", "Sprites/Menue UI/settings_hover.dds",
		GameObjectTag::SettingsButton);
	settingsButton->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.53f));
	settingsButton->SetLayer(100);
	settingsButton->SetPanStrengthFactor(0);
	AddInterfaceElement(settingsButton);
	
	auto quitButton = std::make_shared<MenuButton>(this, "Sprites/Menue UI/pause/main menu.dds", "Sprites/Menue UI/pause/main menu_hover.dds",
		GameObjectTag::QuitButton);
	quitButton->SetPosition(CU::Vector2(width * 0.5f, height * 0.63f));
	quitButton->SetLayer(100);
	quitButton->SetPanStrengthFactor(0);
	AddGameObject(quitButton);
}

void PauseMenu::MouseClicked(GameObject* aTarget)
{
	if (aTarget == nullptr) return;

	GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Misc/Menu_Button.wav");

	const GameObjectTag targetTag = aTarget->GetTag();

	switch (targetTag)
	{
	case GameObjectTag::StartButton:
		myPauseIsActive = false;
		break;

	case GameObjectTag::RestartButton:
		myPauseIsActive = false;
		GetLevelManagerProxy()->RestartCurrentLevel();
		break;

	case GameObjectTag::SettingsButton:
		mySettings = std::make_unique<Settings>(Settings::eBackTarget::ePauseMenu);
		mySettings->OnEnter(GetSceneManagerProxy(), GetLevelManagerProxy(), GetGlobalServiceProvider());
		mySettings->Init();
		mySettingIsActive = true;
		break;

	case GameObjectTag::QuitButton:
		//GetSceneManagerProxy()->Transition(std::make_unique<MainMenu>());
		GetSceneManagerProxy()->TransitionToMainMenu();
		break;
	}
	
}
