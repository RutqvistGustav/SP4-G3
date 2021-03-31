#include "stdafx.h"
#include "EnemyManager.h"

#include "UpdateContext.h"
#include "RenderContext.h"

#include "Enemy.h"
#include "EnemyFactory.h"
#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "GameMessenger.h"
#include "EnemyDeathMessage.h"
#include "Vector2.hpp"

#include "Minimap.h"

EnemyManager::EnemyManager(Scene* aScene, Minimap* aMinimap) :
	myScene(aScene),
	myMinimap(aMinimap)
{
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::SpawnEnemy, this);
}

EnemyManager::~EnemyManager()
{
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::SpawnEnemy, this);
}

void EnemyManager::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	DeleteMarkedEnemies();
}

void EnemyManager::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{}

void EnemyManager::AddEnemy(EnemyFactory::EnemyType anEnemyType, CU::Vector2<float> aPosition, std::shared_ptr<GameObject> aTarget, const PowerUpType& aLootType)
{
	std::shared_ptr<Enemy> enemy = EnemyFactory::CreateEnemy(anEnemyType, myScene);
	enemy->SetPosition(aPosition);
	enemy->Init();
	enemy->SetLootType(aLootType);

	if (aTarget != nullptr)
	{
		enemy->SetTarget(aTarget);
	}

	myEnemies.push_back(enemy);
	myScene->AddGameObject(enemy);

	myMinimap->AddObject(enemy.get(), Minimap::MapObjectType::Enemy);
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

GameMessageAction EnemyManager::OnMessage(const GameMessage aMessage, const EnemyMessageData* someMessageData)
{
	AddEnemy(someMessageData->myEnemyType, someMessageData->mySpawnPosition, someMessageData->myTarget, someMessageData->myLootType);
	return GameMessageAction::Keep;
}

void EnemyManager::DeleteMarkedEnemies()
{
	for (int enemyIndex = static_cast<int>(myEnemies.size()) - 1; enemyIndex >= 0; enemyIndex--)
	{
		if (myEnemies[enemyIndex]->GetDeleteThisFrame())
		{
			SendDeathMessage(myEnemies[enemyIndex]->GetLootType(), myEnemies[enemyIndex]->GetPosition());

			auto eraseIt = myEnemies.begin() + enemyIndex;

			myMinimap->RemoveObject(eraseIt->get());

			myEnemies.erase(eraseIt);
		}
	}
}
