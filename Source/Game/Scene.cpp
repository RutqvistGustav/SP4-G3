#include "stdafx.h"
#include "Scene.h"

#include "SceneManagerProxy.h"
#include "MousePointer.h"

Scene::Scene() = default;
Scene::~Scene() = default;

void Scene::Update(const float /*aDeltaTime*/, UpdateContext& /*anUpdateContext*/)
{
}

void Scene::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
{
}

void Scene::OnEnter(SceneManagerProxy* aSceneManagerProxy, GlobalServiceProvider* aGlobalServiceProvider)
{
	assert(aSceneManagerProxy != nullptr);
	assert(mySceneManagerProxy == nullptr);

	myMousePointer = std::make_unique<MousePointer>(this);
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

Camera* Scene::GetCamera()
{
	assert(GetSceneManagerProxy() != nullptr);

	return GetSceneManagerProxy()->GetCamera();
}
