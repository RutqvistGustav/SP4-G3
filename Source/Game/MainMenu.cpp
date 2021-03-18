#include "stdafx.h"
#include "MainMenu.h"
#include "Metrics.h"
#include "MousePointer.h"
#include "SceneManagerProxy.h"
#include "GameScene.h"
#include "MenuButton.h"
#include "CollisionManager.h"
#include "Options.h"

MainMenu::MainMenu()
{
}

MainMenu::~MainMenu()
{
}

void MainMenu::Init()
{
	float x = Metrics::GetReferenceSize().x;
	float y = Metrics::GetReferenceSize().y;

	myStartButton = std::make_unique<MenuButton>(this, "Sprites/StartButton.png");
	myStartButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.10f));
	myStartButton->SetType(GameObject::eObjectType::PlayButton);
	myButtons.push_back(std::move(myStartButton));

	myOptionsButton = std::make_unique<MenuButton>(this, "Sprites/OptionsButton.png");
	myOptionsButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.50f));
	myOptionsButton->SetType(GameObject::eObjectType::OptionsButton);
	myButtons.push_back(std::move(myOptionsButton));

	myQuitButton = std::make_unique<MenuButton>(this, "Sprites/QuitButton.png");
	myQuitButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.90f));
	myQuitButton->SetType(GameObject::eObjectType::QuitButton);
	myButtons.push_back(std::move(myQuitButton));

}

void MainMenu::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	CollisionManager::GetInstance()->Update();

	for (auto& o : myButtons)
	{
		o->Update(aDeltaTime, anUpdateContext);
	}

	myMousePointer->Update(aDeltaTime, anUpdateContext);

	if (myMousePointer->ButtonClicked())
	{
		switch (myMousePointer->ClickedButton())
		{
		case GameObject::eObjectType::PlayButton:
		{
			GetSceneManagerProxy()->Transition(std::make_unique<GameScene>());
			break;
		}
		case GameObject::eObjectType::OptionsButton:
		{
			GetSceneManagerProxy()->Transition(std::make_unique<Options>());
			break;
		}
		case GameObject::eObjectType::QuitButton:
		{
			PostMessage(*Tga2D::CEngine::GetInstance()->GetHWND(), WM_USER + 0, 0, 0);
			break;
		}
		}
	}
}

void MainMenu::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	for (auto& o : myButtons)
	{
		o->Render(aRenderQueue, aRenderContext);
	}

	myMousePointer->Render(aRenderQueue, aRenderContext);
}
