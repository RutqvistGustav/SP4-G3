#include "stdafx.h"
#include "Scene.h"

Scene::Scene() = default;
Scene::~Scene() = default;

void Scene::Update(const float /*aDeltaTime*/, UpdateContext& /*anUpdateContext*/)
{
}

void Scene::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
{
}

void Scene::OnEnter()
{}

void Scene::OnExit()
{}

void Scene::AddGameObject(std::shared_ptr<GameObject> aGameObject)
{
	myGameObjects.push_back(aGameObject);
}
