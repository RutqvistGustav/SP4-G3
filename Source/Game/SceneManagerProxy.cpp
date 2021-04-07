#include "stdafx.h"
#include "SceneManagerProxy.h"

#include "SceneManager.h"
#include "Scene.h"

SceneManagerProxy::SceneManagerProxy(SceneManager& aSceneManager) :
	mySceneManager(aSceneManager)
{}

void SceneManagerProxy::Transition(std::unique_ptr<Scene> aTargetScene)
{
	mySceneManager.Transition(std::move(aTargetScene));
}

void SceneManagerProxy::TransitionToMainMenu()
{
	mySceneManager.TransitionToMainMenu();
}

bool SceneManagerProxy::IsTransitionQueued() const
{
	return mySceneManager.IsTransitionQueued();
}
