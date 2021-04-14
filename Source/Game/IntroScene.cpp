#include "stdafx.h"
#include "IntroScene.h"

#include "UpdateContext.h"
#include "GlobalServiceProvider.h"
#include "LevelManagerProxy.h"
#include "AudioManager.h"
#include "JsonManager.h"
#include "CutscenePlayer.h"

IntroScene::IntroScene() = default;

IntroScene::~IntroScene() = default;

void IntroScene::Init()
{
	myIntro = std::make_unique<CutscenePlayer>();
	nlohmann::json data = GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/VideoPaths.json");
	myIntro->Init(data.at("StartupPath"));

	GetGlobalServiceProvider()->GetAudioManager()->StopAll();
	//GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Cutscenes/Intro.mp3");
}

void IntroScene::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	if (myIntro->IsPlaying())
	{
		myIntro->Update(aDeltaTime);
		SkipCutscene(anUpdateContext);
	}
	else
	{
		GetLevelManagerProxy()->TransitionToLevel(1);
	}
}

void IntroScene::Render(RenderQueue* const aRenderQueue, RenderContext& /*aRenderContext*/)
{
	if (myIntro != nullptr)
	{
		myIntro->Render(aRenderQueue);
	}
}

void IntroScene::SkipCutscene(UpdateContext& anUpdateContext)
{
	if (anUpdateContext.myInputInterface->IsPressingPause())
	{
		GetGlobalServiceProvider()->GetAudioManager()->StopAll();
		myIntro->Stop();
	}
}
