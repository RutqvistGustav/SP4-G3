#include "stdafx.h"
#include "StartupScene.h"

#include "UpdateContext.h"
#include "GlobalServiceProvider.h"
#include "SceneManagerProxy.h"
#include "JsonManager.h"
#include "CutscenePlayer.h"

#include "Controls.h"

StartupScene::StartupScene() = default;

StartupScene::~StartupScene() = default;

void StartupScene::Init()
{
	myIntro = std::make_unique<CutscenePlayer>();
	nlohmann::json data = GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/VideoPaths.json");
	myIntro->Init(data.at("StartupPath"));
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
		GetSceneManagerProxy()->Transition(std::make_unique<Controls>(Controls::BackTarget::MainMenu));
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
	}
}
