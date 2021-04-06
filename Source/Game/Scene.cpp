#include "stdafx.h"
#include "Scene.h"
#include "CollisionManager.h"
#include "MousePointer.h"
#include "GameObject.h"
#include "Camera.h"

Scene::Scene() :
	myCamera({ 0.0f, 0.0f })
{}

Scene::~Scene() = default;

void Scene::Update(const float aDeltaTime, UpdateContext & anUpdateContext)
{
	GetCamera()->Update(aDeltaTime, anUpdateContext);

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

void Scene::OnEnter(SceneManagerProxy* aSceneManagerProxy, LevelManagerProxy* aLevelManagerProxy, GlobalServiceProvider * aGlobalServiceProvider)
{
	assert(aSceneManagerProxy != nullptr);
	assert(mySceneManagerProxy == nullptr);

	assert(aLevelManagerProxy != nullptr);
	assert(myLevelManagerProxy == nullptr);

	assert(aGlobalServiceProvider != nullptr);
	assert(myGlobalServiceProvider == nullptr);

	mySceneManagerProxy = aSceneManagerProxy;
	myLevelManagerProxy = aLevelManagerProxy;
	myGlobalServiceProvider = aGlobalServiceProvider;
}

void Scene::OnExit()
{
	assert(myLevelManagerProxy != nullptr);
	assert(mySceneManagerProxy != nullptr);

	myLevelManagerProxy = nullptr;
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
	return &myCamera;
}
