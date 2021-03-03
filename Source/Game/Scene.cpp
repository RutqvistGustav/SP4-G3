#include "stdafx.h"
#include "Scene.h"

Scene::~Scene()
{
}

void Scene::Update(const float aDeltaTime)
{
}

void Scene::Render()
{
}

void Scene::AddGameObject(std::shared_ptr<GameObject> aGameObject)
{
	myGameObjects.push_back(aGameObject);
}
