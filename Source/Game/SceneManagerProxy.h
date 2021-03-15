#pragma once

#include <memory>

class JsonManager;
class WeaponFactory;
class Camera;

class Scene;
class SceneManager;

class SceneManagerProxy
{
public:

	SceneManagerProxy(SceneManager& aSceneManager);

	void Transition(std::unique_ptr<Scene> aTargetScene);

	JsonManager* GetJsonManager();
	WeaponFactory* GetWeaponFactory();
	Camera* GetCamera();

private:

	SceneManager& mySceneManager;

};
