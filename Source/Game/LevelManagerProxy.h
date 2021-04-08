#pragma once

class SceneManager;

// NOTE: TODO: Because of laziness SceneManager is reused,
// but because we use the interface through this proxy it can easily and seamlessly get swapped out!
class LevelManagerProxy
{
public:

	LevelManagerProxy(SceneManager& aSceneManager);

	void TransitionToLevel(int aLevelIndex);
	void TransitionToMainMenu();

	void TransitionNextLevel();
	void RestartCurrentLevel();

	int GetCurrentLevelIndex() const;

	bool InLevel() const;

	void SaveCheckpoint();
	void LoadCheckpoint();

private:

	SceneManager& mySceneManager;

};
