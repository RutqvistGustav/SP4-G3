#include "stdafx.h"
#include "Settings.h"
#include "Metrics.h"
#include "MousePointer.h"
#include "SceneManagerProxy.h"
#include "GameScene.h"
#include "MenuButton.h"
#include "Slider.h"
#include "CollisionManager.h"
#include "MainMenu.h"
#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"
#include "Game.h"

#include "GlobalServiceProvider.h"
#include "AudioManager.h"

#include <iostream>

Settings::Settings() = default;
Settings::~Settings() = default;

void Settings::Init()
{
	MenuScene::Init();

	InitSprites();
	InitSliders();
	InitButtons();

	myMousePointer->SetClickCallback(std::bind(&Settings::MouseClicked, this, std::placeholders::_1));

	Tga2D::SEngineCreateParameters engineParameters;
	SetResolutionBool(engineParameters.myWindowHeight);
}

void Settings::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	MenuScene::Render(aRenderQueue, aRenderContext);

	for (auto& sprite : mySprites)
	{
		aRenderQueue->Queue(RenderCommand(sprite));
	}

	RenderResolutionText(aRenderQueue, aRenderContext);
}

void Settings::InitSprites()
{
	const float width = Metrics::GetReferenceSize().x;
	const float height = Metrics::GetReferenceSize().y;

	auto background = std::make_shared<SpriteWrapper>("Sprites/Menue UI/menu background.dds");
	background->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.5f));
	background->SetLayer(-1);
	mySprites.push_back(background);

	auto settingsSprites = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/settings.dds");
	settingsSprites->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.23f));
	mySprites.push_back(settingsSprites);

	auto resolutionSprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/resolution bar.dds");
	resolutionSprite->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.7f));
	mySprites.push_back(resolutionSprite);

	my720Sprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/720.dds");
	my720Sprite->SetPosition(CommonUtilities::Vector2(width * 0.59f, height * 0.72f));

	my900Sprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/900.dds");
	my900Sprite->SetPosition(CommonUtilities::Vector2(width * 0.59f, height * 0.72f));

	my1080Sprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/1080.dds");
	my1080Sprite->SetPosition(CommonUtilities::Vector2(width * 0.59f, height * 0.72f));
}

void Settings::InitSliders()
{
	AudioManager* audioManager = GetGlobalServiceProvider()->GetAudioManager();

	const float width = Metrics::GetReferenceSize().x;
	const float height = Metrics::GetReferenceSize().y;

	auto masterVolume = std::make_shared<Slider>(this, "Sprites/Menue UI/settings/master bar.dds", GameObjectTag::MasterSlider);
	masterVolume->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.35f), true);
	masterVolume->SetValueChangeCallback(std::bind(&Settings::SetMasterVolume, this, std::placeholders::_1));
	masterVolume->Init();
	masterVolume->SetSlidePercentage(audioManager->GetMasterVolume());
	AddInterfaceElement(masterVolume);

	auto sfxVolume = std::make_shared<Slider>(this, "Sprites/Menue UI/settings/sfx bar.dds", GameObjectTag::SfxSlider);
	sfxVolume->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.45f), true);
	sfxVolume->SetValueChangeCallback(std::bind(&Settings::SetSfxVolume, this, std::placeholders::_1));
	sfxVolume->Init();
	sfxVolume->SetSlidePercentage(audioManager->GetSfxVolume());
	AddInterfaceElement(sfxVolume);

	auto musicVolume = std::make_shared<Slider>(this, "Sprites/Menue UI/settings/music bar.dds", GameObjectTag::MusicSlider);
	musicVolume->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.55f), true);
	musicVolume->SetValueChangeCallback(std::bind(&Settings::SetMusicVolume, this, std::placeholders::_1));
	musicVolume->Init();
	musicVolume->SetSlidePercentage(audioManager->GetMusicVolume());
	AddInterfaceElement(musicVolume);
}

void Settings::InitButtons()
{
	const float width = Metrics::GetReferenceSize().x;
	const float height = Metrics::GetReferenceSize().y;

	auto backButton = std::make_shared<MenuButton>(this, "Sprites/Menue UI/back.dds", "Sprites/Menue UI/back_hover.dds",
		GameObjectTag::BackButton);
	backButton->SetPosition(CommonUtilities::Vector2(width * 0.5f, height* 0.85f));
	AddInterfaceElement(backButton);

	auto leftArrow = std::make_shared<MenuButton>(this, "Sprites/Menue UI/settings/arrow left.dds", "Sprites/Menue UI/settings/arrow left.dds",
		GameObjectTag::ArrowLeftButton);
	leftArrow->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.71f));
	leftArrow->SetColliderSize(CU::Vector2(1.1f, 1.1f));
	AddInterfaceElement(leftArrow);

	auto rightArrow = std::make_shared<MenuButton>(this, "Sprites/Menue UI/settings/arrow right.dds", "Sprites/Menue UI/settings/arrow right.dds",
		GameObjectTag::ArrowRightButton);
	rightArrow->SetPosition(CommonUtilities::Vector2(width * 0.68f, height * 0.71f));
	rightArrow->SetColliderSize(CU::Vector2(1.1f, 1.1f));
	AddInterfaceElement(rightArrow);
}

void Settings::SetResolution(int aResolutionY)
{
	switch (aResolutionY)
	{
	case 720:
	{
		//CGame::GetInstance()->QueueSetResolution(1280, 720);
		break;
	}
	case 900:
	{
		//CGame::GetInstance()->QueueSetResolution(1600, 900);
		break;
	}
	case 1080:
	{
		//CGame::GetInstance()->QueueSetResolution(1920, 1280);
		break;
	}
	}
}

void Settings::SetResolutionBool(int aResolutionY)
{
	switch (aResolutionY)
	{
	case 720:
	{
		my720 = true;
		break;
	}
	case 900:
	{
		my900 = true;
		break;
	}
	case 1080:
	{
		my1080 = true;
		break;
	}
	}
}

void Settings::RenderResolutionText(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	if (my720)
	{
		aRenderQueue->Queue(RenderCommand(my720Sprite));
	}
	else if (my900)
	{
		aRenderQueue->Queue(RenderCommand(my900Sprite));
	}
	else if (my1080)
	{
		aRenderQueue->Queue(RenderCommand(my1080Sprite));
	}
}

void Settings::ChangeResolution(GameObjectTag aTag)
{
	if (aTag == GameObjectTag::ArrowLeftButton)
	{
		if (my720)
		{
			SetResolution(1080);
			my1080 = true;
			my720 = false;
			return;
		}
		else if (my900)
		{
			SetResolution(720);
			my720 = true;
			my900 = false;
			return;
		}
		else if (my1080)
		{
			SetResolution(900);
			my900 = true;
			my1080 = false;
			return;
		}
	}
	if (aTag == GameObjectTag::ArrowRightButton)
	{
		if (my720)
		{
			SetResolution(900);
			my900 = true;
			my720 = false;
			return;
		}
		else if (my900)
		{
			SetResolution(1080);
			my1080 = true;
			my900 = false;
			return;
		}
		else if (my1080)
		{
			SetResolution(720);
			my720 = true;
			my1080 = false;
			return;
		}
	}
}

void Settings::MouseClicked(GameObject* aTarget)
{
	if (aTarget == nullptr)
	{
		return;
	}

	const GameObjectTag targetTag = aTarget->GetTag();

	switch (targetTag)
	{
	case GameObjectTag::ArrowLeftButton:
		ChangeResolution(GameObjectTag::ArrowLeftButton);
		break;
	case GameObjectTag::ArrowRightButton:
		ChangeResolution(GameObjectTag::ArrowRightButton);
		break;

	case GameObjectTag::BackButton:
		GetSceneManagerProxy()->Transition(std::make_unique<MainMenu>());
		break;
	}
}

void Settings::SetMasterVolume(float aVolume)
{
	GetGlobalServiceProvider()->GetAudioManager()->SetMasterVolume(aVolume);
}

void Settings::SetSfxVolume(float aVolume)
{
	GetGlobalServiceProvider()->GetAudioManager()->SetSfxVolume(aVolume);
}

void Settings::SetMusicVolume(float aVolume)
{
	GetGlobalServiceProvider()->GetAudioManager()->SetMusicVolume(aVolume);
}
