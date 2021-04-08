#include "stdafx.h"
#include "LevelManagerProxy.h"

#include "SceneManager.h"

LevelManagerProxy::LevelManagerProxy(SceneManager& aSceneManager) :
	mySceneManager(aSceneManager)
{}

void LevelManagerProxy::TransitionToLevel(int aLevelIndex)
{
	mySceneManager.TransitionToLevel(aLevelIndex);
}

void LevelManagerProxy::TransitionToMainMenu()
{
	mySceneManager.TransitionToMainMenu();
}

void LevelManagerProxy::TransitionNextLevel()
{
	mySceneManager.TransitionNextLevel();
}

void LevelManagerProxy::RestartCurrentLevel()
{
	mySceneManager.RestartCurrentLevel();
}

int LevelManagerProxy::GetCurrentLevelIndex() const
{
	return mySceneManager.GetCurrentLevelIndex();
}

bool LevelManagerProxy::InLevel() const
{
	return mySceneManager.InLevel();
}

void LevelManagerProxy::SaveCheckpoint()
{
	mySceneManager.SaveCheckpoint();
}

void LevelManagerProxy::LoadCheckpoint()
{
	mySceneManager.LoadCheckpoint();
}
