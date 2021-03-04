#pragma once

#include "LockedSection.h"

#include <memory>

class Camera;
struct UpdateContext;
struct RenderContext;
class RenderQueue;
class Scene;

class SceneManager
{
public:

	SceneManager();
	~SceneManager();

	void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	void Transition(std::unique_ptr<Scene> aTargetScene);

	inline Camera* GetCamera() { return myCamera.get(); }

private:

	void RunTransition(std::unique_ptr<Scene> aTargetScene);
	bool HasQueuedTransition() const;

private:
	
	LockedSection myActiveSceneLock;

	std::unique_ptr<Scene> myActiveScene;
	std::unique_ptr<Scene> myQueuedScene;

	std::unique_ptr<Camera> myCamera;

};
