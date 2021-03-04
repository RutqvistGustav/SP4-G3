#pragma once

#include "LockedSection.h"

#include <memory>

struct UpdateContext;
struct RenderContext;
class RenderQueue;
class Scene;

class SceneManager
{
public:

	SceneManager(/* Camera* aCamera */);
	~SceneManager();

	void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	void Transition(std::unique_ptr<Scene> aTargetScene);

private:

	void RunTransition(std::unique_ptr<Scene> aTargetScene);
	bool HasQueuedTransition() const;

private:

	// NOTE: Uncomment when camera has been created
	// Camera* myCamera;
	
	LockedSection myActiveSceneLock;

	std::unique_ptr<Scene> myActiveScene;
	std::unique_ptr<Scene> myQueuedScene;

};
