#pragma once

#include "LockedSection.h"
#include "SceneManagerProxy.h"

#include <memory>

class Camera;
struct UpdateContext;
struct RenderContext;
class RenderQueue;
class Scene;
class JsonManager;
class WeaponFactory;

class SceneManager
{
public:

	SceneManager(
		JsonManager* aJsonManager,
		WeaponFactory* aWeaponFactory);
	~SceneManager();

	void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	void Transition(std::unique_ptr<Scene> aTargetScene);

	inline JsonManager* GetJsonManager() { return myJsonManager; }
	inline WeaponFactory* GetWeaponFactory() { return myWeaponFactory; }
	inline Camera* GetCamera() { return myCamera.get(); }

private:

	void RunTransition(std::unique_ptr<Scene> aTargetScene);
	bool HasQueuedTransition() const;

private:

	SceneManagerProxy myProxy;

	LockedSection myActiveSceneLock;

	JsonManager* myJsonManager;
	WeaponFactory* myWeaponFactory;

	std::unique_ptr<Scene> myActiveScene;
	std::unique_ptr<Scene> myQueuedScene;

	std::unique_ptr<Camera> myCamera;

};
