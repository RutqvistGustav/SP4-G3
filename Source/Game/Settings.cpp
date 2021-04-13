#include "stdafx.h"
#include "Settings.h"
#include "Metrics.h"
#include "MousePointer.h"
#include "SceneManagerProxy.h"
#include "GameScene.h"
#include "MenuButton.h"
#include "Slider.h"
#include "CollisionManager.h"
#include "MainMenu.h"
#include "PauseMenu.h"
#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"
#include "Game.h"

#include "GlobalServiceProvider.h"
#include "AudioManager.h"

#include "SpriteUtil.h"

Settings::Settings() = default;

Settings::Settings(eBackTarget aTarget)
	: myBackTarget(aTarget)
{
}
Settings::~Settings() = default;

void Settings::Init()
{
	MenuScene::Init();

	InitSprites();
	InitSliders();
	InitButtons();

	myMousePointer->SetClickCallback(std::bind(&Settings::MouseClicked, this, std::placeholders::_1));

	// NOTE: TODO: Set default resolution
}

void Settings::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	MenuScene::Render(aRenderQueue, aRenderContext);

	for (auto& sprite : mySprites)
	{
		aRenderQueue->Queue(RenderCommand(sprite));
	}

	RenderResolutionText(aRenderQueue, aRenderContext);
}

bool Settings::IsSettingsActive()
{
	return myIsActive;
}

void Settings::InitSprites()
{
	const float width = Metrics::GetReferenceSize().x;
	const float height = Metrics::GetReferenceSize().y;

	auto background = std::make_shared<SpriteWrapper>("Sprites/Menue UI/menu background.dds");
	background->SetSamplerFilter(RenderSamplerFilter::Bilinear);
	background->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.5f));
	background->SetLayer(-1);

	SpriteUtil::SetSpriteRect(background, Metrics::GetReferenceSize(), { 0.5f, 0.0f });

	mySprites.push_back(background);

	auto settingsSprites = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/settings.dds");
	settingsSprites->SetSamplerFilter(RenderSamplerFilter::Bilinear);
	settingsSprites->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.23f));
	settingsSprites->SetPanStrengthFactor(0);
	settingsSprites->SetLayer(100);
	mySprites.push_back(settingsSprites);

	auto resolutionSprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/resolution bar.dds");
	resolutionSprite->SetSamplerFilter(RenderSamplerFilter::Bilinear);
	resolutionSprite->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.7f));
	resolutionSprite->SetPanStrengthFactor(0);
	resolutionSprite->SetLayer(100);
	mySprites.push_back(resolutionSprite);

	my720Sprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/720.dds");
	my720Sprite->SetSamplerFilter(RenderSamplerFilter::Bilinear);
	my720Sprite->SetPosition(CommonUtilities::Vector2(width * 0.59f, height * 0.72f));
	my720Sprite->SetPanStrengthFactor(0);
	my720Sprite->SetLayer(101);

	my900Sprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/900.dds");
	my900Sprite->SetSamplerFilter(RenderSamplerFilter::Bilinear);
	my900Sprite->SetPosition(CommonUtilities::Vector2(width * 0.59f, height * 0.72f));
	my900Sprite->SetPanStrengthFactor(0);
	my900Sprite->SetLayer(101);

	my1080Sprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/1080.dds");
	my1080Sprite->SetSamplerFilter(RenderSamplerFilter::Bilinear);
	my1080Sprite->SetPosition(CommonUtilities::Vector2(width * 0.59f, height * 0.72f));
	my1080Sprite->SetPanStrengthFactor(0);
	my1080Sprite->SetLayer(101);
}

void Settings::InitSliders()
{
	AudioManager* audioManager = GetGlobalServiceProvider()->GetAudioManager();

	const float width = Metrics::GetReferenceSize().x;
	const float height = Metrics::GetReferenceSize().y;

	auto masterVolume = std::make_shared<Slider>(this, "Sprites/Menue UI/settings/master bar.dds", GameObjectTag::MasterSlider);
	masterVolume->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.35f), true);
	masterVolume->SetValueChangeCallback(std::bind(&Settings::SetMasterVolume, this, std::placeholders::_1));
	masterVolume->Init();
	masterVolume->SetSlidePercentage(audioManager->GetMasterVolume());
	masterVolume->SetPanStrengthFactor(0);
	masterVolume->SetLayer(101);
	AddInterfaceElement(masterVolume);

	auto sfxVolume = std::make_shared<Slider>(this, "Sprites/Menue UI/settings/sfx bar.dds", GameObjectTag::SfxSlider);
	sfxVolume->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.45f), true);
	sfxVolume->SetValueChangeCallback(std::bind(&Settings::SetSfxVolume, this, std::placeholders::_1));
	sfxVolume->Init();
	sfxVolume->SetSlidePercentage(audioManager->GetSfxVolume());
	sfxVolume->SetPanStrengthFactor(0);
	sfxVolume->SetLayer(101);
	AddInterfaceElement(sfxVolume);

	auto musicVolume = std::make_shared<Slider>(this, "Sprites/Menue UI/settings/music bar.dds", GameObjectTag::MusicSlider);
	musicVolume->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.55f), true);
	musicVolume->SetValueChangeCallback(std::bind(&Settings::SetMusicVolume, this, std::placeholders::_1));
	musicVolume->Init();
	musicVolume->SetSlidePercentage(audioManager->GetMusicVolume());
	musicVolume->SetPanStrengthFactor(0);
	musicVolume->SetLayer(101);
	AddInterfaceElement(musicVolume);
}

void Settings::InitButtons()
{
	const float width = Metrics::GetReferenceSize().x;
	const float height = Metrics::GetReferenceSize().y;

	auto backButton = std::make_shared<MenuButton>(this, "Sprites/Menue UI/back.dds", "Sprites/Menue UI/back_hover.dds",
		GameObjectTag::BackButton);
	backButton->SetPosition(CommonUtilities::Vector2(width * 0.5f, height* 0.85f));
	backButton->SetPanStrengthFactor(0);
	backButton->SetLayer(102);
	AddInterfaceElement(backButton);

	auto leftArrow = std::make_shared<MenuButton>(this, "Sprites/Menue UI/settings/arrow left.dds", "Sprites/Menue UI/settings/arrow left.dds",
		GameObjectTag::ArrowLeftButton);
	leftArrow->SetPosition(CommonUtilities::Vector2(width * 0.5f, height * 0.71f));
	leftArrow->SetColliderSize(CU::Vector2(1.1f, 1.1f));
	leftArrow->SetPanStrengthFactor(0);
	leftArrow->SetLayer(102);
	AddInterfaceElement(leftArrow);

	auto rightArrow = std::make_shared<MenuButton>(this, "Sprites/Menue UI/settings/arrow right.dds", "Sprites/Menue UI/settings/arrow right.dds",
		GameObjectTag::ArrowRightButton);
	rightArrow->SetPosition(CommonUtilities::Vector2(width * 0.68f, height * 0.71f));
	rightArrow->SetColliderSize(CU::Vector2(1.1f, 1.1f));
	rightArrow->SetPanStrengthFactor(0);
	rightArrow->SetLayer(102);
	AddInterfaceElement(rightArrow);
}

void Settings::SetResolution(Resolution aResolution)
{
	int width;
	int height;

	switch (aResolution)
	{
	case Resolution::R1280x720:
		width = 1280;
		height = 720;
		break;

	case Resolution::R1600x900:
		width = 1600;
		height = 900;
		break;

	case Resolution::R1920x1080:
		width = 1920;
		height = 1080;
		break;

	default:
		return;
	}

	myResolution = aResolution;

	CGame::QueueSetResolution(width, height);
}

void Settings::RenderResolutionText(RenderQueue* const aRenderQueue, RenderContext& /*aRenderContext*/)
{
	switch (myResolution)
	{
	case Resolution::R1280x720:
		aRenderQueue->Queue(RenderCommand(my720Sprite));
		break;

	case Resolution::R1600x900:
		aRenderQueue->Queue(RenderCommand(my900Sprite));
		break;

	default:
	case Resolution::R1920x1080:
		aRenderQueue->Queue(RenderCommand(my1080Sprite));
		break;
	}
}

void Settings::SlideResolution(int anAmount)
{
	constexpr int resolutionsCount = static_cast<int>(Resolution::Count);

	static_assert(resolutionsCount > 0, "Not enough available resolutions!");

	int targetResolution = static_cast<int>(myResolution) + anAmount;

	if (targetResolution < 0)
	{
		targetResolution = resolutionsCount - 1;
	}

	targetResolution %= resolutionsCount;

	SetResolution(static_cast<Resolution>(targetResolution));
}

void Settings::MouseClicked(GameObject* aTarget)
{
	if (aTarget == nullptr)
	{
		return;
	}

	GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Misc/Menu_Button.wav");

	const GameObjectTag targetTag = aTarget->GetTag();

	switch (targetTag)
	{
	case GameObjectTag::ArrowLeftButton:
		SlideResolution(-1);
		break;
	case GameObjectTag::ArrowRightButton:
		SlideResolution(1);
		break;

	case GameObjectTag::BackButton:
		if (myBackTarget == eBackTarget::eMainMenu)
		{
			GetSceneManagerProxy()->Transition(std::make_unique<MainMenu>(), false);
		}
		else if (myBackTarget == eBackTarget::ePauseMenu)
		{
			myIsActive = false;
		}
		
		break;
	}
}

void Settings::SetMasterVolume(float aVolume)
{
	GetGlobalServiceProvider()->GetAudioManager()->SetMasterVolume(aVolume);
}

void Settings::SetSfxVolume(float aVolume)
{
	GetGlobalServiceProvider()->GetAudioManager()->SetSfxVolume(aVolume);
}

void Settings::SetMusicVolume(float aVolume)
{
	GetGlobalServiceProvider()->GetAudioManager()->SetMusicVolume(aVolume);
}
