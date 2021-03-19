#pragma once

#include <memory>
#include <vector>

class Camera;
class GameObject;
struct UpdateContext;
struct RenderContext;
class RenderQueue;
class SceneManagerProxy;
class JsonManager;
class WeaponFactory;
class MousePointer;
class GlobalServiceProvider;

class Scene
{
public:
	
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	virtual void OnEnter(SceneManagerProxy* aSceneManagerProxy, GlobalServiceProvider* aGlobalServiceProvider);
	virtual void OnExit();
	
	virtual void AddGameObject(std::shared_ptr<GameObject> aGameObject);

	Camera* GetCamera();

	inline SceneManagerProxy* GetSceneManagerProxy() { return mySceneManagerProxy; }
	inline GlobalServiceProvider* GetGlobalServiceProvider() { return myGlobalServiceProvider; }
	
protected:

	std::unique_ptr<MousePointer> myMousePointer;
	std::vector<std::shared_ptr<GameObject>> myGameObjects;

private:

	SceneManagerProxy* mySceneManagerProxy{};
	GlobalServiceProvider* myGlobalServiceProvider{};

};
