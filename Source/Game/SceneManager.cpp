#include "stdafx.h"
#include "SceneManager.h"

#include "Camera.h"

#include "Scene.h"

#include <cassert>

SceneManager::SceneManager()
{
	myCamera = std::make_unique<Camera>(CU::Vector2<float>(0.0f, 0.0f));
}

SceneManager::~SceneManager()
{
	if (myActiveScene != nullptr)
	{
		myActiveScene->OnExit(this);
	}
}

void SceneManager::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	assert(myActiveScene != nullptr);

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

void SceneManager::RunTransition(std::unique_ptr<Scene> aTargetScene)
{
	if (myActiveScene != nullptr)
	{
		myActiveScene->OnExit(this);
	}

	myActiveScene = std::move(aTargetScene);

	if (myActiveScene != nullptr)
	{
		myActiveScene->OnEnter(this);
	}
}

bool SceneManager::HasQueuedTransition() const
{
	return myQueuedScene != nullptr;
}