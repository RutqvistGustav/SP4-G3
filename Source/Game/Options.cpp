#include "stdafx.h"
#include "Options.h"
#include "Metrics.h"
#include "MenuButton.h"
#include "MousePointer.h"
#include "CollisionManager.h"
#include "GameScene.h"
#include "SceneManagerProxy.h"

Options::Options()
{
}

Options::~Options()
{
}

void Options::Init()
{
	float x = Metrics::GetReferenceSize().x;
	float y = Metrics::GetReferenceSize().y;

	myMuteSound = std::make_unique<MenuButton>(this, "Sprites/StartButton.png");
	myMuteSound->SetPosition(CommonUtilities::Vector2(x / 2, y * 0.3f));
	myMuteSound->SetType(GameObject::eObjectType::MuteSound);
	myButtons.push_back(std::move(myMuteSound));
}

void Options::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
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
		case GameObject::eObjectType::MuteSound:
		{
			break;
		}
		}
	}
}

void Options::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
}
