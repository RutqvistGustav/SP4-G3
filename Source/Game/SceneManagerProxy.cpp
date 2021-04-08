#include "stdafx.h"
#include "SceneManagerProxy.h"

#include "SceneManager.h"
#include "Scene.h"

SceneManagerProxy::SceneManagerProxy(SceneManager& aSceneManager) :
	mySceneManager(aSceneManager)
{}

void SceneManagerProxy::Transition(std::unique_ptr<Scene> aTargetScene, bool aHasAnimation)
{
	mySceneManager.Transition(std::move(aTargetScene), aHasAnimation);
}

bool SceneManagerProxy::IsTransitionQueued() const
{
	return mySceneManager.IsTransitionQueued();
}
