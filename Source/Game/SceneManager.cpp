#include "stdafx.h"
#include "SceneManager.h"

#include "Camera.h"

#include "Scene.h"

#include "MainMenu.h"
#include "GameScene.h"

#include "CheckpointMessage.h"

#include "GlobalServiceProvider.h"
#include "AudioManager.h"
#include "GameMessenger.h"

#include <cassert>

SceneManager::SceneManager(GlobalServiceProvider* aGlobalServiceProvider) :
	myGlobalServiceProvider(aGlobalServiceProvider),
	mySceneManagerProxy(*this),
	myLevelManagerProxy(*this)
{}

SceneManager::~SceneManager()
{
	RunTransition(nullptr);
}

void SceneManager::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	assert(myActiveScene != nullptr);

	if (HasQueuedTransition())
	{
		RunTransition(std::move(myQueuedScene));
	}

	if (myHasQueuedCheckpointLoad)
	{
		LoadCheckpoint();

		myHasQueuedCheckpointLoad = false;
	}

	myActiveSceneLock.Lock();

	myActiveScene->Update(aDeltaTime, anUpdateContext);

	myActiveSceneLock.Unlock();
}

void SceneManager::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	assert(aRenderQueue != nullptr);
	assert(myActiveScene != nullptr);

	myActiveSceneLock.Lock();

	myActiveScene->Render(aRenderQueue, aRenderContext);

	myActiveSceneLock.Unlock();
}

void SceneManager::Transition(std::unique_ptr<Scene> aTargetScene)
{
	if (myActiveSceneLock.IsLocked())
	{
		myQueuedScene = std::move(aTargetScene);
	}
	else
	{
		RunTransition(std::move(aTargetScene));
	}
}

bool SceneManager::IsTransitionQueued() const
{
	return HasQueuedTransition();
}

void SceneManager::TransitionToLevel(int aLevelIndex)
{
	assert(aLevelIndex > 0);

	std::string levelPath = "Maps/Level";
	levelPath += std::to_string(aLevelIndex);
	levelPath += ".json";

	Transition(std::make_unique<GameScene>(levelPath));

	myCurrentLevel = aLevelIndex;
}

void SceneManager::TransitionToMainMenu()
{
	Transition(std::make_unique<MainMenu>());

	myCurrentLevel = -1;
}

void SceneManager::RestartCurrentLevel()
{
	assert(InLevel());

	if (myLastCheckpoint.HasData())
	{
		if (myActiveSceneLock.IsLocked())
		{
			myHasQueuedCheckpointLoad = true;
		}
		else
		{
			LoadCheckpoint();
		}
	}
	else
	{
		TransitionToLevel(GetCurrentLevelIndex());
	}
}

int SceneManager::GetCurrentLevelIndex() const
{
	return myCurrentLevel;
}

bool SceneManager::InLevel() const
{
	return GetCurrentLevelIndex() >= 0;
}

void SceneManager::SaveCheckpoint()
{
	assert(InLevel());

	myLastCheckpoint.Clear();

	CheckpointMessageData checkpointMessageData{};
	checkpointMessageData.myCheckpointContext = &myLastCheckpoint;

	myGlobalServiceProvider->GetGameMessenger()->Send(GameMessage::CheckpointSave, &checkpointMessageData);
}

void SceneManager::LoadCheckpoint()
{
	assert(InLevel());

	CheckpointMessageData checkpointMessageData{};
	checkpointMessageData.myCheckpointContext = &myLastCheckpoint;

	myGlobalServiceProvider->GetGameMessenger()->Send(GameMessage::CheckpointLoad, &checkpointMessageData);
}

Camera* SceneManager::GetCamera()
{
	if (myActiveScene == nullptr)
	{
		return nullptr;
	}

	return myActiveScene->GetCamera();
}

void SceneManager::PlayMusic()
{
	if (GetCurrentLevelIndex() != EMusic::MainMenuMusic)
	{
		myIsMainMusicPlaying = false;
		myGlobalServiceProvider->GetAudioManager()->StopAll();
	}
	else if(myIsMainMusicPlaying == false)
	{
		myGlobalServiceProvider->GetAudioManager()->StopAll();
	}

	switch (GetCurrentLevelIndex())
	{
	case EMusic::Level01:
	{
		myGlobalServiceProvider->GetAudioManager()->Play("Sound/Music/1. Unbreakable.mp3", 0.5f, true);
		break;
	}
	case EMusic::Level02:
	{
		myGlobalServiceProvider->GetAudioManager()->Play("Sound/Music/2.Hard Rock.mp3", 0.5f, true);
		break;
	}
	case EMusic::Level03:
	{
		myGlobalServiceProvider->GetAudioManager()->Play("Sound/Music/10.Heart of Warrior.mp3", 0.5f, true);
		break;
	}
	case EMusic::MainMenuMusic:
	{
		if (myIsMainMusicPlaying == false)
		{
			myGlobalServiceProvider->GetAudioManager()->Play("Sound/Music/7.Rage Machine.mp3", 0.5f, true);
			myIsMainMusicPlaying = true;
		}
		
		break;
	}
	}
}

void SceneManager::RunTransition(std::unique_ptr<Scene> aTargetScene)
{
	if (myActiveScene != nullptr)
	{
		myActiveScene->OnExit();
	}

	myActiveScene = std::move(aTargetScene);

	if (myActiveScene != nullptr)
	{
		myActiveScene->OnEnter(&mySceneManagerProxy, &myLevelManagerProxy, myGlobalServiceProvider);
		myActiveScene->Init();
	}

	PlayMusic();
}

bool SceneManager::HasQueuedTransition() const
{
	return myQueuedScene != nullptr;
}
