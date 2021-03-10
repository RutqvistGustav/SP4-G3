#include "stdafx.h"
#include "Scene.h"

#include "SceneManager.h"

Scene::Scene() = default;
Scene::~Scene() = default;

void Scene::Update(const float /*aDeltaTime*/, UpdateContext& /*anUpdateContext*/)
{
}

void Scene::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
{
}

void Scene::OnEnter(SceneManager* aSceneManager)
{
	assert(aSceneManager != nullptr);
	assert(mySceneManager == nullptr);

	mySceneManager = aSceneManager;
}

void Scene::OnExit(SceneManager* aSceneManager)
{
	assert(aSceneManager != nullptr);
	assert(mySceneManager == aSceneManager);

	mySceneManager = nullptr;
}

void Scene::AddGameObject(std::shared_ptr<GameObject> aGameObject)
{
	myGameObjects.push_back(aGameObject);
}

JsonManager* Scene::GetJsonManager()
{
	assert(GetSceneManager() != nullptr);

	return GetSceneManager()->GetJsonManager();
}

WeaponFactory* Scene::GetWeaponFactory()
{
	assert(GetSceneManager() != nullptr);

	return GetSceneManager()->GetWeaponFactory();
}

Camera* Scene::GetCamera()
{
	assert(GetSceneManager() != nullptr);

	return GetSceneManager()->GetCamera();
}
