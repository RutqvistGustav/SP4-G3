#include "stdafx.h"
#include "LevelSelect.h"
#include "MousePointer.h"
#include "CollisionManager.h"
#include "MenuButton.h"
#include "MainMenu.h"
#include "LevelManagerProxy.h"
#include "SceneManagerProxy.h"
#include "GameScene.h"
#include "Metrics.h"
#include "RenderCommand.h"
#include "RenderQueue.h"
#include "SpriteWrapper.h"

#include "GlobalServiceProvider.h"
#include "AudioManager.h"

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

#ifdef _DEBUG

	myCollisionManager->RenderDebug(aRenderQueue, aRenderContext);

#endif
}

void LevelSelect::InitButtons()
{
	const float width = Metrics::GetReferenceSize().x;
	const float height = Metrics::GetReferenceSize().y;

	constexpr int levelCount = 3;
	constexpr float levelBoxWidth = 480.0f;

	const float startX = width * 0.5f - levelBoxWidth * (levelCount / 2);

	for (int i = 0; i < levelCount; ++i)
	{
		const GameObjectTag buttonTag = static_cast<GameObjectTag>(static_cast<int>(GameObjectTag::Level1Button) + i);

		auto levelButton = std::make_shared<MenuButton>(this, "Sprites/Menue UI/lvlsellect.dds", "Sprites/Menue UI/lvlsellect.dds", buttonTag);
		levelButton->SetPosition(CommonUtilities::Vector2(startX + i * levelBoxWidth, height * 0.50f));
		levelButton->SetColliderSize({ 0.7f, 0.7f });

		AddInterfaceElement(levelButton);
	}

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

	GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Misc/Menu_Button.wav");

	const GameObjectTag targetTag = aTarget->GetTag();

	switch (targetTag)
	{
	case GameObjectTag::Level1Button:
		GetLevelManagerProxy()->TransitionToLevel(1);
		break;
	case GameObjectTag::Level2Button:
		GetLevelManagerProxy()->TransitionToLevel(2);
		break;
	case GameObjectTag::Level3Button:
		GetLevelManagerProxy()->TransitionToLevel(3);
		break;

	case GameObjectTag::BackButton:
		GetSceneManagerProxy()->Transition(std::make_unique<MainMenu>(), false);
		break;
	}
}
