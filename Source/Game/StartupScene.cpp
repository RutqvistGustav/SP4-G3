#include "stdafx.h"
#include "StartupScene.h"

#include "UpdateContext.h"
#include "GlobalServiceProvider.h"
#include "LevelManagerProxy.h"
#include "JsonManager.h"
#include "CutscenePlayer.h"
#include "AudioManager.h"

StartupScene::StartupScene() = default;

StartupScene::~StartupScene() = default;

void StartupScene::Init()
{
	myIntro = std::make_unique<CutscenePlayer>();
	nlohmann::json data = GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/VideoPaths.json");
	myIntro->Init(data.at("StartupPath"));
	GetGlobalServiceProvider()->GetAudioManager()->SetMasterVolume(1.0f);
	GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Cutscenes/Startup.mp3");
}

void StartupScene::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	if (myIntro->IsPlaying())
	{
		myIntro->Update(aDeltaTime);
		SkipCutscene(anUpdateContext);
	}
	else
	{
		GetGlobalServiceProvider()->GetAudioManager()->SetMasterVolume(0.5f);
		GetLevelManagerProxy()->TransitionToMainMenu();
	}
}

void StartupScene::Render(RenderQueue* const aRenderQueue, RenderContext& /*aRenderContext*/)
{
	if (myIntro != nullptr)
	{
		myIntro->Render(aRenderQueue);
	}
}

void StartupScene::SkipCutscene(UpdateContext& anUpdateContext)
{
	if (anUpdateContext.myInputInterface->IsPressingPause())
	{
		myIntro->Stop();
		GetGlobalServiceProvider()->GetAudioManager()->SetMasterVolume(0.5f);
		GetGlobalServiceProvider()->GetAudioManager()->StopAll();
	}
}
