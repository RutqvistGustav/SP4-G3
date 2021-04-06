#include "stdafx.h"
#include "SceneManager.h"

#include "Camera.h"

#include "Scene.h"

#include "MainMenu.h"
#include "GameScene.h"

#include <cassert>

SceneManager::SceneManager(GlobalServiceProvider* aGlobalServiceProvider) :
	myGlobalServiceProvider(aGlobalServiceProvider),
	myProxy(*this)

{
	myCamera = std::make_unique<Camera>(CU::Vector2<float>(0.0f, 0.0f));
}

SceneManager::~SceneManager()
{
	RunTransition(nullptr);
}

void SceneManager::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	assert(myActiveScene != nullptr);

	myCamera->Update(aDeltaTime, anUpdateContext);

	if (HasQueuedTransition())
	{
		RunTransition(std::move(myQueuedScene));
	}

	myActiveSceneLock.Lock();

	myActiveScene->Update(aDeltaTime, anUpdateContext);

	myActiveSceneLock.Unlock();
}

void SceneManager::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	assert(aRenderQueue != nullptr);
	assert(myActiveScene != nullptr);

	myActiveSceneLock.Lock();

	myActiveScene->Render(aRenderQueue, aRenderContext);

	myActiveSceneLock.Unlock();
}

void SceneManager::Transition(std::unique_ptr<Scene> aTargetScene)
{
	if (myActiveSceneLock.IsLocked())
	{
		myQueuedScene = std::move(aTargetScene);
	}
	else
	{
		RunTransition(std::move(aTargetScene));
	}
}

bool SceneManager::IsTransitionQueued() const
{
	return HasQueuedTransition();
}

void SceneManager::TransitionToLevel(int aLevelIndex)
{
	assert(aLevelIndex >= 0);

	std::string levelPath = "Maps/Level";
	levelPath += std::to_string(aLevelIndex);
	levelPath += ".json";

	Transition(std::make_unique<GameScene>(levelPath.c_str()));

	myCurrentLevel = aLevelIndex;
}

void SceneManager::TransitionToMainMenu()
{
	Transition(std::make_unique<MainMenu>());

	myCurrentLevel = -1;
}

void SceneManager::RestartCurrentLevel()
{
	assert(InLevel());

	TransitionToLevel(GetCurrentLevelIndex());
}

int SceneManager::GetCurrentLevelIndex() const
{
	return myCurrentLevel;
}

bool SceneManager::InLevel() const
{
	return GetCurrentLevelIndex() >= 0;
}

void SceneManager::RunTransition(std::unique_ptr<Scene> aTargetScene)
{
	if (myActiveScene != nullptr)
	{
		myActiveScene->OnExit();
	}

	myActiveScene = std::move(aTargetScene);

	if (myActiveScene != nullptr)
	{
		myActiveScene->OnEnter(&myProxy, myGlobalServiceProvider);
		myActiveScene->Init();
	}
}

bool SceneManager::HasQueuedTransition() const
{
	return myQueuedScene != nullptr;
}
