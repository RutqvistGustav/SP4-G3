#include "stdafx.h"
#include "Scene.h"
#include "CollisionManager.h"

#include "GameObject.h"

#include "SceneManagerProxy.h"
#include "MousePointer.h"

Scene::Scene() = default;
Scene::~Scene() = default;

void Scene::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	for (std::shared_ptr<GameObject>& gameObject : myGameObjects)
	{
		gameObject->Update(aDeltaTime, anUpdateContext);
	}
}

void Scene::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	for (std::shared_ptr<GameObject>& gameObject : myGameObjects)
	{
		gameObject->Render(aRenderQueue, aRenderContext);
	}
}

void Scene::OnEnter(SceneManagerProxy* aSceneManagerProxy)
{
	assert(aSceneManagerProxy != nullptr);
	assert(mySceneManagerProxy == nullptr);

	myMousePointer = std::make_unique<MousePointer>(this);
	mySceneManagerProxy = aSceneManagerProxy;
}

void Scene::OnExit(SceneManagerProxy* aSceneManagerProxy)
{
	assert(aSceneManagerProxy != nullptr);
	assert(mySceneManagerProxy == aSceneManagerProxy);

	mySceneManagerProxy = nullptr;
}

void Scene::AddGameObject(std::shared_ptr<GameObject> aGameObject)
{
	myGameObjects.push_back(aGameObject);
}

JsonManager* Scene::GetJsonManager()
{
	assert(GetSceneManagerProxy() != nullptr);

	return GetSceneManagerProxy()->GetJsonManager();
}

WeaponFactory* Scene::GetWeaponFactory()
{
	assert(GetSceneManagerProxy() != nullptr);

	return GetSceneManagerProxy()->GetWeaponFactory();
}

Camera* Scene::GetCamera()
{
	assert(GetSceneManagerProxy() != nullptr);

	return GetSceneManagerProxy()->GetCamera();
}
