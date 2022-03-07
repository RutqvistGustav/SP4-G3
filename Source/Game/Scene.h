#pragma once

#include "Camera.h"
#include "GameObjectTag.h"

#include <memory>
#include <vector>

class GameObject;
struct UpdateContext;
struct RenderContext;
class RenderQueue;
class LevelManagerProxy;
class SceneManagerProxy;
class JsonManager;
class WeaponFactory;
class CollisionManager;
class GlobalServiceProvider;
class MousePointer;

class Scene
{
public:
	
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	virtual void OnEnter(SceneManagerProxy* aSceneManagerProxy, LevelManagerProxy* aLevelManagerProxy, GlobalServiceProvider* aGlobalServiceProvider);
	virtual void OnExit();
	
	virtual void AddGameObject(std::shared_ptr<GameObject> aGameObject);

	virtual void RemoveMarkedObjects();

	Camera* GetCamera();

	inline SceneManagerProxy* GetSceneManagerProxy() { return mySceneManagerProxy; }
	inline LevelManagerProxy* GetLevelManagerProxy() { return myLevelManagerProxy; }

	inline CollisionManager* GetCollisionManager() { return myCollisionManager.get(); }

	inline GlobalServiceProvider* GetGlobalServiceProvider() { return myGlobalServiceProvider; }

protected:

	std::unique_ptr<CollisionManager> myCollisionManager;
	std::vector<std::shared_ptr<GameObject>> myGameObjects;
	GlobalServiceProvider* myGlobalServiceProvider{};

private:

	SceneManagerProxy* mySceneManagerProxy{};
	LevelManagerProxy* myLevelManagerProxy{};

	Camera myCamera;

};
