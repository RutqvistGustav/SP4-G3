#include "stdafx.h"
#include "SceneManager.h"

#include "Camera.h"

#include "Scene.h"

#include "MainMenu.h"
#include "GameScene.h"
#include "IntroScene.h"
#include "OutroScene.h"

#include "CheckpointMessage.h"

#include "GlobalServiceProvider.h"
#include "AudioManager.h"
#include "GameMessenger.h"

#include "RenderQueue.h"
#include "RenderCommand.h"

#include "Metrics.h"
#include "SpriteWrapper.h"

#include <cassert>

SceneManager::SceneManager(GlobalServiceProvider* aGlobalServiceProvider) :
	myGlobalServiceProvider(aGlobalServiceProvider),
	mySceneManagerProxy(*this),
	myLevelManagerProxy(*this)
{
	myFadeSprite = std::make_shared<SpriteWrapper>();
	myFadeSprite->SetSize(Metrics::GetReferenceSize());
	myFadeSprite->SetPosition(Metrics::GetReferenceSize() * 0.5f);
	myFadeSprite->SetLayer(GameLayer::Transitions);
	myFadeSprite->SetColor(Tga2D::CColor(0.0f, 0.0f, 0.0f, 0.0f));
	myFadeSprite->SetPanStrengthFactor(0.0f);
}

SceneManager::~SceneManager()
{
	RunTransition(nullptr);
}

void SceneManager::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	assert(myActiveScene != nullptr);

	if (myFadeProgress >= 0.0f)
	{
		myFadeProgress += aDeltaTime * ourFadeSpeed;

		if (myFadeProgress >= 0.5f && myFadeDoneCallback != nullptr)
		{
			myFadeDoneCallback();
			myFadeDoneCallback = nullptr;
		}

		const float alpha = 1.0f - std::abs((myFadeProgress - 0.5f) * 2.0f);
		myFadeSprite->SetColor(Tga2D::CColor(0.0f, 0.0f, 0.0f, alpha));

		// NOTE: Reset / done condition
		if (myFadeProgress >= 1.0f) myFadeProgress = -1.0f;
	}
	else
	{
		myActiveSceneLock.Lock();

		myActiveScene->Update(aDeltaTime, anUpdateContext);

		myActiveSceneLock.Unlock();
	}
}

void SceneManager::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	assert(aRenderQueue != nullptr);
	assert(myActiveScene != nullptr);

	myActiveSceneLock.Lock();

	myActiveScene->Render(aRenderQueue, aRenderContext);

	myActiveSceneLock.Unlock();

	if (myFadeProgress >= 0.0f)
	{
		aRenderQueue->Queue(RenderCommand(myFadeSprite));
	}
}

void SceneManager::Transition(std::unique_ptr<Scene> aTargetScene, bool aHasAnimation)
{
	if (IsTransitionQueued())
		return;

	if (myActiveScene == nullptr)
	{
		RunTransition(std::move(aTargetScene));
	}
	else
	{
		Scene* rawTargetScene = aTargetScene.release();
		FadeAndQueueCallback([this, rawTargetScene] { RunTransition(std::unique_ptr<Scene>(rawTargetScene)); });

		if (!aHasAnimation)
		{
			myFadeProgress = 1.0f;
		}
	}
}

bool SceneManager::IsTransitionQueued() const
{
	return myFadeProgress >= 0.0f;
}

void SceneManager::TransitionToLevel(int aLevelIndex)
{
	if (IsTransitionQueued())
		return;

	assert(aLevelIndex > 0);

	std::string levelPath = "Maps/Level";
	levelPath += std::to_string(aLevelIndex);
	levelPath += ".json";

	Transition(std::make_unique<GameScene>(levelPath));

	myCurrentLevel = aLevelIndex;
}

void SceneManager::TransitionToMainMenu()
{
	if (IsTransitionQueued())
		return;

	Transition(std::make_unique<MainMenu>());

	myCurrentLevel = -1;
}

void SceneManager::TransitionNextLevel()
{
	assert(InLevel());

	if (IsTransitionQueued())
		return;

	const int nextLevel = GetCurrentLevelIndex() + 1;

	if (nextLevel > 3)
	{
		// TODO: NOTE: Game complete
		Transition(std::make_unique<OutroScene>());
		//TransitionToMainMenu();
	}
	else if (nextLevel == 0)
	{
		Transition(std::make_unique<IntroScene>());
	}
	else
	{
		TransitionToLevel(nextLevel);
	}
}

void SceneManager::RestartCurrentLevel()
{
	assert(InLevel());

	if (IsTransitionQueued())
		return;

	if (myLastCheckpoint.HasData())
	{
		FadeAndQueueCallback([this]() { LoadCheckpoint(); });
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

void SceneManager::FadeAndQueueCallback(std::function<void()> aFadeCallback)
{
	myFadeDoneCallback = aFadeCallback;
	myFadeProgress = 0.0f;
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
		myGlobalServiceProvider->GetAudioManager()->PlayMusic("Sound/Music/1. Unbreakable.mp3");
		break;
	}
	case EMusic::Level02:
	{
		myGlobalServiceProvider->GetAudioManager()->PlayMusic("Sound/Music/5.Be Faster.mp3");
		break;
	}
	case EMusic::Level03:
	{
		myGlobalServiceProvider->GetAudioManager()->PlayMusic("Sound/Music/10.Heart of Warrior.mp3");
		break;
	}
	case EMusic::MainMenuMusic:
	{
		if (myIsMainMusicPlaying == false)
		{
			myGlobalServiceProvider->GetAudioManager()->PlayMusic("Sound/Music/7.Rage Machine.mp3");
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
