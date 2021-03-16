#include "stdafx.h"
#include "MainMenu.h"
#include "GameObject.h"
#include "Metrics.h"
#include "MousePointer.h"

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
	myButtons.push_back(std::move(myStartButton));

	myQuitButton = std::make_unique<GameObject>(this, "Sprites/QuitButton.png");
	myQuitButton->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.5f));
	myButtons.push_back(std::move(myQuitButton));

	myMousePointer = std::make_unique<MousePointer>(this);
	myMousePointer->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.5f));
}

void MainMenu::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myMousePointer->Update(aDeltaTime, anUpdateContext);

	for (auto& o : myButtons)
	{
		o->Update(aDeltaTime, anUpdateContext);
	}

	if (myMousePointer->GetLMBDown())
	{

	}
}

void MainMenu::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	myMousePointer->Render(aRenderQueue, aRenderContext);

	for (auto& o : myButtons)
	{
		o->Render(aRenderQueue, aRenderContext);
	}
}
