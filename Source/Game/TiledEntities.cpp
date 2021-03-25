#include "stdafx.h"
#include "TiledEntities.h"

#include "TiledParser.h"
#include "GameMessenger.h"
#include "EnemyMessage.h"
#include "GlobalServiceProvider.h"
#include "Scene.h"

TiledEntities::TiledEntities(const TiledParser* aParser, Scene* aScene) :
	myParser(aParser),
	myScene(aScene)
{}

void TiledEntities::SpawnEntities()
{
	for (const auto& entity : myParser->myResult->GetEntities())
	{
		if (entity.GetType() == "Enemy")
		{
			if (entity.GetSubType() == "Zombie")
			{
				EnemyMessageData enemyMessageData{};
				enemyMessageData.myEnemyType = EnemyFactory::EnemyType::Zombie;
				enemyMessageData.mySpawnPosition = entity.GetPosition();
				
				myScene->GetGlobalServiceProvider()->GetGameMessenger()->Send(GameMessage::SpawnEnemy, &enemyMessageData);
			}
			if (entity.GetSubType() == "EliteZombie")
			{
				EnemyMessageData enemyMessageData{};
				enemyMessageData.myEnemyType = EnemyFactory::EnemyType::EliteZombie;
				enemyMessageData.mySpawnPosition = entity.GetPosition();
				
				myScene->GetGlobalServiceProvider()->GetGameMessenger()->Send(GameMessage::SpawnEnemy, &enemyMessageData);
			}
		}
		
	}
}
