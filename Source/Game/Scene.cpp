#include "stdafx.h"
#include "Scene.h"

#include "SceneManagerProxy.h"

Scene::Scene() = default;
Scene::~Scene() = default;

void Scene::Update(const float /*aDeltaTime*/, UpdateContext& /*anUpdateContext*/)
{
}

void Scene::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
{
}

void Scene::OnEnter(SceneManagerProxy* aSceneManagerProxy)
{
	assert(aSceneManagerProxy != nullptr);
	assert(mySceneManagerProxy == nullptr);

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
