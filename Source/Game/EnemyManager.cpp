#include "stdafx.h"
#include "EnemyManager.h"

#include "UpdateContext.h"
#include "RenderContext.h"

#include "Enemy.h"
#include "EnemyFactory.h"
#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "GameMessenger.h"
#include "Vector2.hpp"

EnemyManager::EnemyManager(Scene* aScene) :
	myScene(aScene)
{
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::SpawnEnemy, this);
}

EnemyManager::~EnemyManager()
{
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::SpawnEnemy, this);
}

void EnemyManager::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	for (std::shared_ptr<Enemy> enemy : myEnemies)
	{
		enemy->Update(aDeltaTime, anUpdateContext);
	}
}

void EnemyManager::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	for (std::shared_ptr<Enemy> enemy : myEnemies)
	{
		enemy->Render(aRenderQueue, aRenderContext);
	}
}

void EnemyManager::AddEnemy(EnemyFactory::EnemyType anEnemyType, CU::Vector2<float> aPosition)
{
	std::shared_ptr<Enemy> enemy = EnemyFactory::CreateEnemy(anEnemyType, myScene);
	enemy->SetPosition(aPosition);
	enemy->Init();

	myEnemies.push_back(enemy);
	myScene->AddGameObject(enemy);
}

GameMessageAction EnemyManager::OnMessage(const GameMessage aMessage, const EnemyMessageData* someMessageData)
{
	AddEnemy(someMessageData->myEnemyType, someMessageData->mySpawnPosition);
	return GameMessageAction::Keep;
}

void EnemyManager::DeleteMarkedEnemies()
{
	for (int enemyIndex = static_cast<int>(myEnemies.size()); enemyIndex >= 0; enemyIndex--)
	{
		if (myEnemies[enemyIndex]->GetDeleteThisFrame())
		{
			myEnemies.erase(myEnemies.begin() + enemyIndex);
		}
	}
}
