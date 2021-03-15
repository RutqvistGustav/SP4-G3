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

JsonManager* SceneManagerProxy::GetJsonManager()
{
	return mySceneManager.GetJsonManager();
}

WeaponFactory* SceneManagerProxy::GetWeaponFactory()
{
	return mySceneManager.GetWeaponFactory();
}

Camera* SceneManagerProxy::GetCamera()
{
	return mySceneManager.GetCamera();
}
