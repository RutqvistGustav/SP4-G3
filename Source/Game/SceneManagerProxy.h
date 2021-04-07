#pragma once

#include <memory>

class Camera;

class Scene;
class SceneManager;

class SceneManagerProxy
{
public:

	SceneManagerProxy(SceneManager& aSceneManager);

	void Transition(std::unique_ptr<Scene> aTargetScene);

	bool IsTransitionQueued() const;

private:

	SceneManager& mySceneManager;

};
