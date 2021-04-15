#include "stdafx.h"

#include "Controls.h"
#include "RenderQueue.h"
#include "RenderCommand.h"
#include "SpriteWrapper.h"
#include "Metrics.h"
#include "MenuButton.h"
#include "GlobalServiceProvider.h"
#include "AudioManager.h"
#include "SceneManagerProxy.h"
#include "LevelManagerProxy.h"
#include "MainMenu.h"
#include "MousePointer.h"

#include "SpriteUtil.h"

Controls::Controls(BackTarget aTarget) :
	MenuScene(),
	myBackTarget(aTarget)
{}

void Controls::Init()
{
	MenuScene::Init();

	myMousePointer->SetClickCallback(std::bind(&Controls::MouseClicked, this, std::placeholders::_1));

	const float width = Metrics::GetReferenceSize().x;
	const float height = Metrics::GetReferenceSize().y;

	auto background = std::make_shared<SpriteWrapper>("Sprites/Menue UI/controller meny.dds");
	background->SetSamplerFilter(RenderSamplerFilter::Bilinear);
	background->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.5f));
	background->SetLayer(100);
	
	SpriteUtil::SetSpriteRect(background, Metrics::GetReferenceSize(), { 0.5f, 0.0f });

	mySprites.push_back(background);


	auto backButton = std::make_shared<MenuButton>(this, "Sprites/Menue UI/back.dds", "Sprites/Menue UI/back_hover.dds",
		GameObjectTag::BackButton);
	backButton->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.9f));
	backButton->SetLayer(101);
	AddInterfaceElement(backButton);
	myBackButtonIndex = myGameObjects.size() - 1;
}

void Controls::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	MenuScene::Render(aRenderQueue, aRenderContext);

	for (auto& sprite : mySprites)
	{
		aRenderQueue->Queue(RenderCommand(sprite));
	}
}

void Controls::MouseClicked(GameObject* aTarget)
{
	if (aTarget == nullptr)
	{
		return;
	}

	GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Misc/Menu_Button.wav");

	if (myBackTarget == BackTarget::MainMenu)
	{
		GetSceneManagerProxy()->Transition(std::make_unique<MainMenu>(), false);
	}
	else
	{
		GetLevelManagerProxy()->TransitionToLevel(1);
		myIsActive = false;
	}
}