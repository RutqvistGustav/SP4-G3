#include "stdafx.h"
#include "MainMenu.h"
#include "GameObject.h"
#include "Metrics.h"
#include "MousePointer.h"
#include "SceneManagerProxy.h"
#include "GameScene.h"

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

	myStartButton = std::make_unique<GameObject>(this, "Sprites/StartButton.png");
	myStartButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.4f));
	myStartButton->SetType(GameObject::eObjectType::PlayButton);
	myButtons.push_back(std::move(myStartButton));

	myQuitButton = std::make_unique<GameObject>(this, "Sprites/QuitButton.png");
	myQuitButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.5f));
	myQuitButton->SetType(GameObject::eObjectType::QuitButton);
	myButtons.push_back(std::move(myQuitButton));

	myMousePointer = std::make_unique<MousePointer>(this);
}

void MainMenu::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myMousePointer->Update(aDeltaTime, anUpdateContext);

	for (auto& o : myButtons)
	{
		o->Update(aDeltaTime, anUpdateContext);
	}

	if (myMousePointer->ButtonClicked())
	{
		switch (myMousePointer->ClickedButton())
		{
		case GameObject::eObjectType::PlayButton:
		{
			GetSceneManagerProxy()->Transition(std::make_unique<GameScene>());
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
