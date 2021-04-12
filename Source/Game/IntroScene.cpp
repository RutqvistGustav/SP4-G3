#include "stdafx.h"
#include "IntroScene.h"

#include "GlobalServiceProvider.h"
#include "LevelManagerProxy.h"
#include "JsonManager.h"
#include "CutscenePlayer.h"

IntroScene::IntroScene() = default;

IntroScene::~IntroScene() = default;

void IntroScene::Init()
{
	myIntro = std::make_unique<CutscenePlayer>();
	nlohmann::json data = GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/VideoPaths.json");
	myIntro->Init(data.at("StartupPath"));
}

void IntroScene::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
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

void IntroScene::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	if (myIntro != nullptr)
	{
		myIntro->Render(aRenderQueue);
	}
}
