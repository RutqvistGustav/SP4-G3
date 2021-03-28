#include "stdafx.h"
#include "LevelSelect.h"
#include "MousePointer.h"
#include "CollisionManager.h"
#include "MenuButton.h"
#include "MainMenu.h"
#include "SceneManagerProxy.h"
#include "GameScene.h"
#include "Metrics.h"
#include "TiledParser.h"
#include "TiledRenderer.h"
#include "TiledCollision.h"
#include "RenderCommand.h"
#include "RenderQueue.h"

LevelSelect::LevelSelect() = default;
LevelSelect::~LevelSelect() = default;

void LevelSelect::Init()
{
	myX = Metrics::GetReferenceSize().x;
	myY = Metrics::GetReferenceSize().y;

	InitCollisions();

	myMousePointer = std::make_unique<MousePointer>(this);

	InitSprites();
	InitButtons();

	SetPanFactors();
}

void LevelSelect::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myCollisionManager->Update();

	for (auto& o : myButtons)
	{
		o->Update();
	}

	myMousePointer->Update(aDeltaTime, anUpdateContext);

	if (myMousePointer->GetButtonClicked())
	{
		switch (myMousePointer->ClickedButton())
		{
		case GameObjectTag::Level1Button:
		{
			GetSceneManagerProxy()->Transition(std::make_unique<GameScene>());
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

void LevelSelect::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	for (auto& s : mySprites)
	{
		RenderCommand renderCommand = RenderCommand(s);
		aRenderQueue->Queue(renderCommand);
	}
	for (auto& o : myButtons)
	{
		o->Render(aRenderQueue, aRenderContext);
	}

	myMousePointer->Render(aRenderQueue, aRenderContext);
}

void LevelSelect::InitCollisions()
{
	myTiledParser = std::make_unique<TiledParser>("Maps/EmptyMap.json");
	myTiledRenderer = std::make_unique<TiledRenderer>(myTiledParser.get());
	myTiledCollision = std::make_unique<TiledCollision>(myTiledParser.get());
	myCollisionManager = std::make_unique<CollisionManager>(myTiledCollision.get());
}

void LevelSelect::InitSprites()
{
	myBackground = std::make_shared<SpriteWrapper>("Sprites/Menue UI/menu background.dds");
	myBackground->SetPosition(CommonUtilities::Vector2(myX * 0.5f, myY * 0.5f));
	mySprites.push_back(std::move(myBackground));
}

void LevelSelect::InitButtons()
{
	float x = Metrics::GetReferenceSize().x;
	float y = Metrics::GetReferenceSize().y;

	myLevel1 = std::make_unique<MenuButton>(this, "Sprites/Menue UI/lvlsellect.dds", "Sprites/Menue UI/lvlsellect.dds", GameObjectTag::Level1Button);
	myLevel1->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.50f));
	myLevel1->SetColliderSize(CU::Vector2(1.f, .8f));
	myButtons.push_back(std::move(myLevel1));

	myBackButton = std::make_unique<MenuButton>(this, "Sprites/Menue UI/back.dds", "Sprites/Menue UI/back.dds", GameObjectTag::BackButton);
	myBackButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.85f));
	myButtons.push_back(std::move(myBackButton));
}

void LevelSelect::SetPanFactors()
{
	for (auto& s : mySprites)
	{
		s->SetPanStrengthFactor(0);
	}
}
