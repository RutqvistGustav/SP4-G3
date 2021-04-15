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

#include "TextWrapper.h"

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

	FindAvailableResolutions();
	DetectResolution();
}

void Settings::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	MenuScene::Update(aDeltaTime, anUpdateContext);

	DetectResolution();
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

void Settings::FindAvailableResolutions()
{
	DWORD modeNum = 0;
	DEVMODEA devMode;
	ZeroMemory(&devMode, sizeof(devMode));
	devMode.dmSize = sizeof(DEVMODEA);

	std::set<Resolution> resolutionSet;

	while (EnumDisplaySettingsExA(nullptr, modeNum, &devMode, 0) != FALSE)
	{
		++modeNum;

		constexpr float targetRatio = 16.0f / 9.0f;
		const float ratio = static_cast<float>(devMode.dmPelsWidth) / static_cast<float>(devMode.dmPelsHeight);

		if (std::abs(targetRatio - ratio) < 0.01f)
		{
			resolutionSet.insert(
				{
					static_cast<int>(devMode.dmPelsWidth),
					static_cast<int>(devMode.dmPelsHeight)
				}
			);
		}
	}

	myResolutions = std::vector<Resolution>(resolutionSet.begin(), resolutionSet.end());

	std::sort(myResolutions.begin(), myResolutions.end(), [](const Resolution& aL, const Resolution& aR)
	{
		int sizeL = aL.myWidth * aL.myHeight;
		int sizeR = aR.myWidth * aR.myHeight;

		return sizeL < sizeR;
	});
}

void Settings::DetectResolution()
{
	const VECTOR2UI resolution = Tga2D::CEngine::GetInstance()->GetWindowSize();

	if (resolution == myPrevDetectedResolution)
		return;

	myPrevDetectedResolution = resolution;

	std::vector<Resolution> bestMatchResolutions = myResolutions;

	const int resolutionSize = static_cast<int>(resolution.myX * resolution.myY);

	std::sort(bestMatchResolutions.begin(), bestMatchResolutions.end(), [resolutionSize](const Resolution& aL, const Resolution& aR)
	{
		const int lSize = aL.myWidth * aL.myHeight;
		const int rSize = aR.myWidth * aR.myHeight;

		return std::abs(resolutionSize - lSize) < std::abs(resolutionSize - rSize);
	});

	Resolution bestMatchResolution = bestMatchResolutions.front();

	auto bestMatchIt = std::find(myResolutions.begin(), myResolutions.end(), bestMatchResolution);

	assert(bestMatchIt != myResolutions.end());

	SetResolutionIndex(static_cast<int>(bestMatchIt - myResolutions.begin()), false);
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

	myResolutionText = std::make_shared<TextWrapper>("Text/Avancement/Avancement2020-Medium(1-5).otf", Tga2D::EFontSize_36, 0);
	myResolutionText->SetPanStrengthFactor(0.0f);
	myResolutionText->SetPivot({ 0.5f, 0.5f });
	myResolutionText->SetPosition({ width * 0.59f, height * 0.705f });
	myResolutionText->SetLayer(101);
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
	backButton->SetPosition(CommonUtilities::Vector2(width * 0.5f, height* 0.9f));
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

void Settings::SetResolutionIndex(int anIndex, bool anUpdateResolution)
{
	assert(anIndex >= 0 && anIndex < static_cast<int>(myResolutions.size()));

	myCurrentResolutionIndex = anIndex;

	const Resolution& targetResolution = myResolutions[myCurrentResolutionIndex];
	myResolutionText->SetText(std::to_string(targetResolution.myWidth) + "x" + std::to_string(targetResolution.myHeight));

	if (anUpdateResolution)
	{
		CGame::QueueSetResolution(targetResolution.myWidth, targetResolution.myHeight);
	}
}

void Settings::RenderResolutionText(RenderQueue* const aRenderQueue, RenderContext& /*aRenderContext*/)
{
	aRenderQueue->Queue(RenderCommand(myResolutionText));
}

void Settings::SlideResolution(int anAmount)
{
	int targetIndex = myCurrentResolutionIndex + anAmount;
	if (targetIndex < 0)
	{
		targetIndex = static_cast<int>(myResolutions.size() - 1);
	}

	targetIndex = targetIndex % static_cast<int>(myResolutions.size());

	SetResolutionIndex(targetIndex, true);
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
