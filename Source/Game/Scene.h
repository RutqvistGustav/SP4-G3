#pragma once

#include <memory>
#include <vector>

class Camera;
class GameObject;
struct UpdateContext;
struct RenderContext;
class RenderQueue;
class SceneManager;
class JsonManager;
class WeaponFactory;

class Scene
{
public:
	
	Scene();
	virtual ~Scene();

	virtual void Init() = 0;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	virtual void OnEnter(SceneManager* aSceneManager);
	virtual void OnExit(SceneManager* aSceneManager);
	
	virtual void AddGameObject(std::shared_ptr<GameObject> aGameObject);

	JsonManager* GetJsonManager();
	WeaponFactory* GetWeaponFactory();
	Camera* GetCamera();
	inline SceneManager* GetSceneManager() { return mySceneManager; }

protected:

	std::vector<std::shared_ptr<GameObject>> myGameObjects;

private:

	SceneManager* mySceneManager{};

};
