#include "stdafx.h"
#include "LevelSelect.h"
#include "MousePointer.h"
#include "CollisionManager.h"
#include "MenuButton.h"
#include "MainMenu.h"
#include "SceneManagerProxy.h"
#include "GameScene.h"
#include "Metrics.h"

LevelSelect::LevelSelect() = default;
LevelSelect::~LevelSelect() = default;

void LevelSelect::Init()
{
	myCollisionManager = std::make_unique<CollisionManager>();
	myMousePointer = std::make_unique<MousePointer>(this);

	InitButtons();
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
	for (auto& o : myButtons)
	{
		o->Render(aRenderQueue, aRenderContext);
	}

	myMousePointer->Render(aRenderQueue, aRenderContext);
}

void LevelSelect::InitButtons()
{
	float x = Metrics::GetReferenceSize().x;
	float y = Metrics::GetReferenceSize().y;

	myLevel1 = std::make_unique<MenuButton>(this, "Sprites/Level1Button.png", "Sprites/Level1Button.png", GameObjectTag::Level1Button);
	myLevel1->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.10f));
	myButtons.push_back(std::move(myLevel1));

	myBackButton = std::make_unique<MenuButton>(this, "Sprites/BackButton.png", "Sprites/Level1Button.png", GameObjectTag::BackButton);
	myBackButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.90f));
	myButtons.push_back(std::move(myBackButton));
}
