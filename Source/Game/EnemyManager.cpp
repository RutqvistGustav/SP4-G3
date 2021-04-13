#include "stdafx.h"
#include "EnemyManager.h"

#include "UpdateContext.h"
#include "RenderContext.h"

#include "CheckpointContext.h"

#include "Enemy.h"
#include "EnemyFactory.h"
#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "GameMessenger.h"
#include "EnemyDeathMessage.h"
#include "Vector2.hpp"

#include <iostream>

EnemyManager::EnemyManager(Scene* aScene) :
	myScene(aScene)
{
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::SpawnEnemy, this);
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::CheckpointSave, this);
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::CheckpointLoad, this);
}

EnemyManager::~EnemyManager()
{
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::CheckpointLoad, this);
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::CheckpointSave, this);
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::SpawnEnemy, this);
}

void EnemyManager::AddEnemy(EnemyType anEnemyType, CU::Vector2<float> aPosition, std::shared_ptr<GameObject> aTarget, const PowerUpType& aLootType, const bool aShouldRoam)
{
	std::shared_ptr<Enemy> enemy = EnemyFactory::CreateEnemy(anEnemyType, myScene);
	enemy->SetPosition(aPosition);
	enemy->SetInitialPosition(aPosition);
	enemy->Init();
	enemy->SetLootType(aLootType);
	enemy->SetShouldRoam(aShouldRoam);

	if (aTarget != nullptr)
	{
		enemy->SetTarget(aTarget);
	}

	myEnemies.push_back(enemy);
	myScene->AddGameObject(enemy);
}

void EnemyManager::AddTargetToAllEnemies(std::shared_ptr<GameObject> aTarget)
{
	for (std::shared_ptr<Enemy> enemy : myEnemies)
	{
		enemy->SetTarget(aTarget);
	}
}

void EnemyManager::SendDeathMessage(const PowerUpType aLootType, const CU::Vector2<float> aSpawnPosition)
{
	EnemyDeathMessageData deathMessage;
	deathMessage.myDeathPosition = aSpawnPosition;
	deathMessage.myLootType = aLootType;
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Send(GameMessage::EnemyDied, &deathMessage);
}

GameMessageAction EnemyManager::OnMessage(const GameMessage aMessage, const CheckpointMessageData* someMessageData)
{
	switch (aMessage)
	{
	case GameMessage::CheckpointSave:
	{
		EnemyManagerCheckpointData* data = someMessageData->myCheckpointContext->NewData<EnemyManagerCheckpointData>("EnemyManager");

		data->myEnemies.reserve(myEnemies.size());
		for (auto& enemy : myEnemies)
		{
			data->myEnemies.push_back({ enemy->GetInitialPosition(), enemy->GetType(), enemy->GetLootType() , enemy->GetShouldRoam()});
		}
	}

		break;

	case GameMessage::CheckpointLoad:
	{
		DeleteAllEnemies();

		EnemyManagerCheckpointData* data = someMessageData->myCheckpointContext->GetData<EnemyManagerCheckpointData>("EnemyManager");

		for (auto& enemyData : data->myEnemies)
		{
			AddEnemy(enemyData.myEnemyType, enemyData.myPosition, nullptr, enemyData.myPowerupType, enemyData.myShouldRoam);
		}
	}

		break;

	default:
		assert(false);
		break;
	}

	return GameMessageAction::Keep;
}

GameMessageAction EnemyManager::OnMessage(const GameMessage /*aMessage*/, const EnemyMessageData* someMessageData)
{
	AddEnemy(someMessageData->myEnemyType, someMessageData->mySpawnPosition, someMessageData->myTarget, someMessageData->myLootType, someMessageData->myShouldRoam);
	return GameMessageAction::Keep;
}

void EnemyManager::DeleteAllEnemies()
{
	for (auto& enemy : myEnemies)
	{
		enemy->SetDeleteThisFrame();
	}
}

void EnemyManager::DeleteMarkedEnemies()
{
	for (int enemyIndex = static_cast<int>(myEnemies.size()) - 1; enemyIndex >= 0; enemyIndex--)
	{
		if (myEnemies[enemyIndex]->GetDeleteThisFrame())
		{
			SendDeathMessage(myEnemies[enemyIndex]->GetLootType(), myEnemies[enemyIndex]->GetPosition());
			
			auto eraseIt = myEnemies.begin() + enemyIndex;

			myEnemies.erase(eraseIt);
		}
	}
}

GameMessageAction EnemyManager::OnMessage(const GameMessage aMessage, const void* someMessageData)
{
	switch (aMessage)
	{
	case GameMessage::SpawnEnemy:
		return OnMessage(aMessage, reinterpret_cast<const EnemyMessageData*>(someMessageData));

	case GameMessage::CheckpointSave:
	case GameMessage::CheckpointLoad:
		return OnMessage(aMessage, reinterpret_cast<const CheckpointMessageData*>(someMessageData));

	default:
		assert(false);
		break;
	}

	return GameMessageAction::Unsubscribe;
}
