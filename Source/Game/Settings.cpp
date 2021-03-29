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
#include "TiledParser.h"
#include "TiledRenderer.h"
#include "TiledCollision.h"
#include "Game.h"

Settings::Settings() = default;
Settings::~Settings() = default;

void Settings::Init()
{
	myX = Metrics::GetReferenceSize().x;
	myY = Metrics::GetReferenceSize().y;

	InitCollisions();

	myMousePointer = std::make_unique<MousePointer>(this);

	InitSprites();
	InitSliders();
	InitButtons();

	SetPanFactors();

	Tga2D::SEngineCreateParameters engineParameters;
	SetResolutionBool(engineParameters.myWindowHeight);
}

void Settings::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myX = Metrics::GetReferenceSize().x;
	myY = Metrics::GetReferenceSize().y;

	myCollisionManager->Update();

	UpdateObjects(aDeltaTime, anUpdateContext);
	UpdateMouse(aDeltaTime, anUpdateContext);
}

void Settings::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	RenderObjects(aRenderQueue, aRenderContext);
	RenderResolutionText(aRenderQueue, aRenderContext);
	myMousePointer->Render(aRenderQueue, aRenderContext);
}

void Settings::InitCollisions()
{
	myTiledParser = std::make_unique<TiledParser>("Maps/EmptyMap.json");
	myTiledRenderer = std::make_unique<TiledRenderer>(myTiledParser.get());
	myTiledCollision = std::make_unique<TiledCollision>(myTiledParser.get());
	myCollisionManager = std::make_unique<CollisionManager>(myTiledCollision.get());
}

void Settings::InitSprites()
{
	myBackground = std::make_shared<SpriteWrapper>("Sprites/Menue UI/menu background.dds");
	myBackground->SetPosition(CommonUtilities::Vector2(myX * 0.5f, myY * 0.5f));
	mySprites.push_back(std::move(myBackground));

	mySettingsSprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/settings.dds");
	mySettingsSprite->SetPosition(CommonUtilities::Vector2(myX * 0.5f, myY * 0.23f));
	mySprites.push_back(std::move(mySettingsSprite));

	myResolutionSprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/resolution bar.dds");
	myResolutionSprite->SetPosition(CommonUtilities::Vector2(myX * 0.5f, myY * 0.7f));
	mySprites.push_back(std::move(myResolutionSprite));

	my720Sprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/720.dds");
	my720Sprite->SetPosition(CommonUtilities::Vector2(myX * 0.59f, myY * 0.72f));
	myResolutionSprites.push_back(my720Sprite);

	my900Sprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/900.dds");
	my900Sprite->SetPosition(CommonUtilities::Vector2(myX * 0.59f, myY * 0.72f));
	myResolutionSprites.push_back(my900Sprite);

	my1080Sprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/1080.dds");
	my1080Sprite->SetPosition(CommonUtilities::Vector2(myX * 0.59f, myY * 0.72f));
	myResolutionSprites.push_back(my1080Sprite);
}

void Settings::InitSliders()
{
	myMasterVolume = std::make_unique<Slider>(this, "Sprites/Menue UI/settings/master bar.dds", GameObjectTag::MasterSlider);
	myMasterVolume->SetPosition(CommonUtilities::Vector2(myX * 0.5f, myY * 0.35f), true);
	mySliders.push_back(std::move(myMasterVolume));

	mySfxVolume = std::make_unique<Slider>(this, "Sprites/Menue UI/settings/sfx bar.dds", GameObjectTag::SfxSlider);
	mySfxVolume->SetPosition(CommonUtilities::Vector2(myX * 0.5f, myY * 0.45f), true);
	mySliders.push_back(std::move(mySfxVolume));

	myMusicVolume = std::make_unique<Slider>(this, "Sprites/Menue UI/settings/music bar.dds", GameObjectTag::MusicSlider);
	myMusicVolume->SetPosition(CommonUtilities::Vector2(myX * 0.5f, myY * 0.55f), true);
	mySliders.push_back(std::move(myMusicVolume));

	for (auto& s : mySliders)
	{
		s->Init();
	}
}

void Settings::InitButtons()
{
	myBackButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/back.dds", "Sprites/Menue UI/back_hover.dds",
		GameObjectTag::BackButton);
	myBackButton->SetPosition(CommonUtilities::Vector2(myX * 0.5f, myY * 0.85f));
	myButtons.push_back(std::move(myBackButton));

	myLeftArrow = std::make_unique<MenuButton>(this, "Sprites/Menue UI/settings/arrow left.dds", "Sprites/Menue UI/settings/arrow left.dds",
		GameObjectTag::ArrowLeftButton);
	myLeftArrow->SetPosition(CommonUtilities::Vector2(myX * 0.5f, myY * 0.71f));
	myLeftArrow->SetColliderSize(CU::Vector2(1.1f, 1.1f));
	myButtons.push_back(std::move(myLeftArrow));

	myRightArrow = std::make_unique<MenuButton>(this, "Sprites/Menue UI/settings/arrow right.dds", "Sprites/Menue UI/settings/arrow right.dds",
		GameObjectTag::ArrowRightButton);
	myRightArrow->SetPosition(CommonUtilities::Vector2(myX * 0.68f, myY * 0.71f));
	myRightArrow->SetColliderSize(CU::Vector2(1.1f, 1.1f));
	myButtons.push_back(std::move(myRightArrow));
}

void Settings::SetPanFactors()
{
	for (auto& s : mySprites)
	{
		s->SetPanStrengthFactor(0);
	}
	for (auto& s : myResolutionSprites)
	{
		s->SetPanStrengthFactor(0);
	}
}

void Settings::RenderObjects(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	for (auto& s : mySprites)
	{
		RenderCommand renderCommand = RenderCommand(s);
		aRenderQueue->Queue(renderCommand);
	}

	for (auto& b : myButtons)
	{
		b->Render(aRenderQueue, aRenderContext);
	}
	for (auto& s : mySliders)
	{
		s->Render(aRenderQueue, aRenderContext);
	}
}

void Settings::UpdateMouse(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myMousePointer->Update(aDeltaTime, anUpdateContext);

	if (myMousePointer->GetButtonClicked())
	{
		switch (myMousePointer->ClickedButton())
		{
		case GameObjectTag::BackButton:
		{
			GetSceneManagerProxy()->Transition(std::make_unique<MainMenu>());
			break;
		}
		case GameObjectTag::ArrowLeftButton:
		{
			ChangeResolution(GameObjectTag::ArrowLeftButton);
			break;
		}
		case GameObjectTag::ArrowRightButton:
		{
			ChangeResolution(GameObjectTag::ArrowRightButton);
			break;
		}
		}
		myMousePointer->SetButtonClicked(false);
	}
}

void Settings::UpdateObjects(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	for (auto& b : myButtons)
	{
		b->Update();
	}
	for (auto& s : mySliders)
	{
		s->Update(aDeltaTime, anUpdateContext, myMousePointer->GetLMBDown(), myMousePointer->GetPointerPos());
	}
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
		RenderCommand renderCommand = RenderCommand(my720Sprite);
		aRenderQueue->Queue(renderCommand);
	}
	if (my900)
	{
		RenderCommand renderCommand = RenderCommand(my900Sprite);
		aRenderQueue->Queue(renderCommand);
	}
	if (my1080)
	{
		RenderCommand renderCommand = RenderCommand(my1080Sprite);
		aRenderQueue->Queue(renderCommand);
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
		if (my900)
		{
			SetResolution(720);
			my720 = true;
			my900 = false;
			return;
		}
		if (my1080)
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
		if (my900)
		{
			SetResolution(1080);
			my1080 = true;
			my900 = false;
			return;
		}
		if (my1080)
		{
			SetResolution(720);
			my720 = true;
			my1080 = false;
			return;
		}
	}
}
