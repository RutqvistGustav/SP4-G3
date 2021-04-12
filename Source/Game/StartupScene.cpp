#include "stdafx.h"
#include "StartupScene.h"

#include "GlobalServiceProvider.h"
#include "LevelManagerProxy.h"
#include "JsonManager.h"
#include "CutscenePlayer.h"

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
	}
	else
	{
		GetLevelManagerProxy()->TransitionToMainMenu();
	}
}

void StartupScene::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	if (myIntro != nullptr)
	{
		myIntro->Render(aRenderQueue);
	}
}
