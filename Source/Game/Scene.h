#pragma once
#include "Scene.h"
#include <memory>
#include <vector>

class GameObject;

class Scene
{
public:
	Scene() = default;
	virtual ~Scene();

	virtual void Update(const float aDeltaTime);
	virtual void Render();
	virtual void AddGameObject(std::shared_ptr<GameObject> aGameObject);

protected:
	std::vector<std::shared_ptr<GameObject>> myGameObjects;
};

