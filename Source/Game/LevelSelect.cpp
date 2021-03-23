#include "stdafx.h"
#include "LevelSelect.h"
#include "MousePointer.h"
#include "CollisionManager.h"
#include "MenuButton.h"
#include "MainMenu.h"
#include "SceneManagerProxy.h"
#include "GameScene.h"
#include "Metrics.h"

LevelSelect::~LevelSelect()
{
}

void LevelSelect::Init()
{
	InitButtons();
}

void LevelSelect::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	CollisionManager::GetInstance()->Update();

	for (auto& o : myButtons)
	{
		o->Update();
	}

	myMousePointer->Update(aDeltaTime, anUpdateContext);

	if (myMousePointer->ButtonClicked())
	{
		switch (myMousePointer->ClickedButton())
		{
		case GameObject::eObjectType::Level1:
		{
			GetSceneManagerProxy()->Transition(std::make_unique<GameScene>());
			break;
		}
		case GameObject::eObjectType::BackButton:
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

	myLevel1 = std::make_unique<MenuButton>(this, "Sprites/Level1Button.png");
	myLevel1->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.10f));
	myLevel1->SetType(GameObject::eObjectType::Level1);
	myButtons.push_back(std::move(myLevel1));

	myBackButton = std::make_unique<MenuButton>(this, "Sprites/BackButton.png");
	myBackButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.90f));
	myBackButton->SetType(GameObject::eObjectType::BackButton);
	myButtons.push_back(std::move(myBackButton));
}
