#include "stdafx.h"
#include "OutroScene.h"

#include "UpdateContext.h"
#include "GlobalServiceProvider.h"
#include "LevelManagerProxy.h"
#include "AudioManager.h"
#include "JsonManager.h"
#include "CutscenePlayer.h"

OutroScene::OutroScene() = default;

OutroScene::~OutroScene() = default;

void OutroScene::Init()
{
	myOutro = std::make_unique<CutscenePlayer>();
	nlohmann::json data = GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/VideoPaths.json");
	myOutro->Init(data.at("OutroPath"));

	GetGlobalServiceProvider()->GetAudioManager()->StopAll();
	//GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Cutscenes/Outro.mp3");
}

void OutroScene::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	if (myOutro->IsPlaying())
	{
		myOutro->Update(aDeltaTime);
		SkipCutscene(anUpdateContext);
	}
	else
	{
		GetLevelManagerProxy()->TransitionToMainMenu();
	}
}

void OutroScene::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	if (myOutro != nullptr)
	{
		myOutro->Render(aRenderQueue);
	}
}

void OutroScene::SkipCutscene(UpdateContext& anUpdateContext)
{
	if (anUpdateContext.myInputInterface->IsPressingPause())
	{
		GetGlobalServiceProvider()->GetAudioManager()->StopAll();
		myOutro->Stop();
	}
}
