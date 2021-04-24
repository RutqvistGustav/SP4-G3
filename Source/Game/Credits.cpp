#include "stdafx.h"

#include "Credits.h"
#include "RenderQueue.h"
#include "RenderCommand.h"
#include "SpriteWrapper.h"
#include "Metrics.h"
#include "MenuButton.h"
#include "GlobalServiceProvider.h"
#include "AudioManager.h"
#include "SceneManagerProxy.h"
#include "MainMenu.h"
#include "MousePointer.h"

#include "SpriteUtil.h"

void Credits::Init()
{
	MenuScene::Init();

	myMousePointer->SetClickCallback(std::bind(&Credits::MouseClicked, this, std::placeholders::_1));


	const float width = Metrics::GetReferenceSize().x;
	const float height = Metrics::GetReferenceSize().y;

	auto background = std::make_shared<SpriteWrapper>("Sprites/Menue UI/CreditScreen.dds");
	background->SetSamplerFilter(RenderSamplerFilter::Bilinear);
	//background->SetPanStrengthFactor(0);
	background->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.5f));
	background->SetLayer(-1);
	
	SpriteUtil::SetSpriteRect(background, Metrics::GetReferenceSize(), { 0.0f, 0.0f });

	mySprites.push_back(background);

	auto backButton = std::make_shared<MenuButton>(this, "Sprites/Menue UI/back.dds", "Sprites/Menue UI/back_hover.dds",
		GameObjectTag::BackButton);
	backButton->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.9f));
	AddInterfaceElement(backButton);
	myBackButtonIndex = myGameObjects.size() - 1;
}

void Credits::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	MenuScene::Render(aRenderQueue, aRenderContext);

	for (auto& sprite : mySprites)
	{
		aRenderQueue->Queue(RenderCommand(sprite));
	}
}

void Credits::MouseClicked(GameObject* aTarget)
{
	if (aTarget == nullptr)
	{
		return;
	}

	GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Misc/Menu_Button.wav");

	GetSceneManagerProxy()->Transition(std::make_unique<MainMenu>(), false);
}