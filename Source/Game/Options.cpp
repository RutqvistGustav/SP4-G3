#include "stdafx.h"
#include "Options.h"
#include "Metrics.h"
#include "MenuButton.h"
#include "MousePointer.h"
#include "CollisionManager.h"
#include "GameScene.h"
#include "SceneManagerProxy.h"
#include "MainMenu.h"
#include "AudioManager.h"

Options::Options()
{
	myIsMuted = false;
}

Options::~Options()
{
}

void Options::Init()
{
	myAudioManager = std::make_unique<AudioManager>();
	myCollisionManager = std::make_unique<CollisionManager>();

	InitButtons();
}

void Options::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myCollisionManager->Update();

	for (auto& o : myButtons)
	{
		o->Update();
	}

	myMousePointer->Update(aDeltaTime, anUpdateContext);

	if (myMousePointer->ButtonClicked())
	{
		switch (myMousePointer->ClickedButton())
		{
		case GameObjectTag::MuteButton:
		{
			MuteSound();
			break;
		}		
		case GameObjectTag::BackButton:
		{
			GetSceneManagerProxy()->Transition(std::make_unique<MainMenu>());
			break;
		}
		}
	}
}

void Options::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	for (auto& o : myButtons)
	{
		o->Render(aRenderQueue, aRenderContext);
	}

	myMousePointer->Render(aRenderQueue, aRenderContext);
}

void Options::InitButtons()
{
	float x = Metrics::GetReferenceSize().x;
	float y = Metrics::GetReferenceSize().y;

	myMuteSound = std::make_unique<MenuButton>(this, "Sprites/MuteButton.png", GameObjectTag::MuteButton);
	myMuteSound->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.3f));
	myButtons.push_back(std::move(myMuteSound));

	myBackButton = std::make_unique<MenuButton>(this, "Sprites/BackButton.png", GameObjectTag::BackButton);
	myBackButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.7f));
	myButtons.push_back(std::move(myBackButton));
}

void Options::MuteSound()
{
	if (!myIsMuted)
	{
		myAudioManager->SetMasterVolume(0.0f);

		myIsMuted = true;
	}
	else
	{
		myAudioManager->SetMasterVolume(0.2f);

		myIsMuted = false;
	}
}
