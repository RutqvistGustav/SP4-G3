#pragma once

#include "LockedSection.h"
#include "SceneManagerProxy.h"
#include "LevelManagerProxy.h"

#include "CheckpointContext.h"

#include <memory>

class Camera;
struct UpdateContext;
struct RenderContext;
class RenderQueue;
class Scene;
class GlobalServiceProvider;

class SceneManager
{
public:

	SceneManager(GlobalServiceProvider* aGlobalServiceProvider);
	~SceneManager();

	void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	void Transition(std::unique_ptr<Scene> aTargetScene);

	bool IsTransitionQueued() const;

	// == LEVEL MANAGER ==
	// NOTE: TODO: Should be split out to a separate class, ex. LevelManager

	void TransitionToLevel(int aLevelIndex);
	void TransitionToMainMenu();

	void RestartCurrentLevel();

	int GetCurrentLevelIndex() const;

	bool InLevel() const;

	void SaveCheckpoint();
	void LoadCheckpoint();

	// =/= LEVEL MANAGER =/=

	Camera* GetCamera();

private:

	void RunTransition(std::unique_ptr<Scene> aTargetScene);
	bool HasQueuedTransition() const;

private:

	SceneManagerProxy mySceneManagerProxy;
	LevelManagerProxy myLevelManagerProxy;

	GlobalServiceProvider* myGlobalServiceProvider;

	LockedSection myActiveSceneLock;

	std::unique_ptr<Scene> myActiveScene;
	std::unique_ptr<Scene> myQueuedScene;

	int myCurrentLevel{ -1 };

	CheckpointContext myLastCheckpoint;

};
