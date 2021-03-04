#pragma once

#include <memory>
#include <vector>

class GameObject;

struct UpdateContext;
struct RenderContext;
class RenderQueue;

class Scene
{
public:
	
	Scene();
	virtual ~Scene();

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	virtual void OnEnter();
	virtual void OnExit();
	
	virtual void AddGameObject(std::shared_ptr<GameObject> aGameObject);

protected:

	std::vector<std::shared_ptr<GameObject>> myGameObjects;

};
