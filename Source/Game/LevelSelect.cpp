#include "stdafx.h"
#include "LevelSelect.h"
#include "MousePointer.h"
#include "CollisionManager.h"
#include "MenuButton.h"
#include "MainMenu.h"
#include "SceneManagerProxy.h"
#include "GameScene.h"
#include "Metrics.h"
#include "RenderCommand.h"
#include "RenderQueue.h"

LevelSelect::LevelSelect() = default;
LevelSelect::~LevelSelect() = default;

void LevelSelect::Init()
{
	MenuScene::Init();

	myBackground = std::make_shared<SpriteWrapper>("Sprites/Menue UI/menu background.dds");
	myBackground->SetPosition(Metrics::GetReferenceSize() * 0.5f);
	myBackground->SetLayer(-1);

	InitButtons();

	myMousePointer->SetClickCallback(std::bind(&LevelSelect::MouseClicked, this, std::placeholders::_1));
}

void LevelSelect::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	MenuScene::Render(aRenderQueue, aRenderContext);

	aRenderQueue->Queue(RenderCommand(myBackground));
}

void LevelSelect::InitButtons()
{
	const float width = Metrics::GetReferenceSize().x;
	const float height = Metrics::GetReferenceSize().y;

	auto level1 = std::make_shared<MenuButton>(this, "Sprites/Menue UI/ProgArt/1.png", "Sprites/Menue UI/ProgArt/1.png", GameObjectTag::Level1Button);
	level1->SetPosition(CommonUtilities::Vector2(width * 0.4f, height * 0.50f));
	level1->SetColliderSize(CU::Vector2(1.f, .8f));
	AddInterfaceElement(level1);

	auto level2 = std::make_shared<MenuButton>(this, "Sprites/Menue UI/ProgArt/2.png", "Sprites/Menue UI/ProgArt/2.png", GameObjectTag::Level2Button);
	level2->SetPosition(CommonUtilities::Vector2(width * .5f, height * 0.50f));
	level2->SetColliderSize(CU::Vector2(1.f, .8f));
	AddInterfaceElement(level2);

	auto level3 = std::make_shared<MenuButton>(this, "Sprites/Menue UI/ProgArt/3.png", "Sprites/Menue UI/ProgArt/3.png", GameObjectTag::Level3Button);
	level3->SetPosition(CommonUtilities::Vector2(width * .6f, height * 0.50f));
	level3->SetColliderSize(CU::Vector2(1.f, .8f));
	AddInterfaceElement(level3);

	auto backButton = std::make_shared<MenuButton>(this, "Sprites/Menue UI/back.dds", "Sprites/Menue UI/back_hover.dds", GameObjectTag::BackButton);
	backButton->SetPosition(CommonUtilities::Vector2(width * .5f, height * 0.85f));
	AddInterfaceElement(backButton);
}

void LevelSelect::MouseClicked(GameObject* aTarget)
{
	if (aTarget == nullptr)
	{
		return;
	}

	const GameObjectTag targetTag = aTarget->GetTag();

	switch (targetTag)
	{
	case GameObjectTag::Level1Button:
		GetSceneManagerProxy()->Transition(std::make_unique<GameScene>("Maps/Level1.json"));
		break;
	case GameObjectTag::Level2Button:
		GetSceneManagerProxy()->Transition(std::make_unique<GameScene>("Maps/Level2.json"));
		break;
	case GameObjectTag::Level3Button:
		GetSceneManagerProxy()->Transition(std::make_unique<GameScene>("Maps/Level3.json"));
		break;

	case GameObjectTag::BackButton:
		GetSceneManagerProxy()->Transition(std::make_unique<MainMenu>());
		break;
	}
}
