#include "stdafx.h"
#include "Scene.h"
#include "CollisionManager.h"

#include "GameObject.h"

#include "SceneManagerProxy.h"

Scene::Scene() = default;
Scene::~Scene() = default;

void Scene::Update(const float aDeltaTime, UpdateContext & anUpdateContext)
{
	for (std::shared_ptr<GameObject>& gameObject : myGameObjects)
	{
		gameObject->Update(aDeltaTime, anUpdateContext);
	}
}

void Scene::Render(RenderQueue* const aRenderQueue, RenderContext & aRenderContext)
{
	for (std::shared_ptr<GameObject>& gameObject : myGameObjects)
	{
		gameObject->Render(aRenderQueue, aRenderContext);
	}
}

void Scene::OnEnter(SceneManagerProxy * aSceneManagerProxy, GlobalServiceProvider * aGlobalServiceProvider)
{
	assert(aSceneManagerProxy != nullptr);
	assert(mySceneManagerProxy == nullptr);

	assert(aGlobalServiceProvider != nullptr);
	assert(myGlobalServiceProvider == nullptr);

	mySceneManagerProxy = aSceneManagerProxy;
	myGlobalServiceProvider = aGlobalServiceProvider;
}

void Scene::OnExit()
{
	assert(mySceneManagerProxy != nullptr);

	mySceneManagerProxy = nullptr;
}

void Scene::AddGameObject(std::shared_ptr<GameObject> aGameObject)
{
	myGameObjects.push_back(aGameObject);
}

void Scene::RemoveMarkedObjects()
{
	for (int objectIndex = static_cast<int>(myGameObjects.size()) - 1; objectIndex >= 0; objectIndex--)
	{
		if (myGameObjects[objectIndex]->GetDeleteThisFrame())
		{
			myGameObjects[objectIndex]->RemoveCollider();
			myGameObjects.erase(myGameObjects.begin() + objectIndex);
		}
	}
}

Camera* Scene::GetCamera()
{
	assert(GetSceneManagerProxy() != nullptr);

	return GetSceneManagerProxy()->GetCamera();
}
