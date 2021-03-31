#include "stdafx.h"
#include "TiledEntities.h"

#include "TiledParser.h"
#include "GameMessenger.h"
#include "EnemyMessage.h"
#include "GlobalServiceProvider.h"
#include "Scene.h"

#include "DialogueBox.h"

#include <cassert>

TiledEntities::TiledEntities(const TiledParser* aParser, Scene* aScene) :
	myParser(aParser),
	myScene(aScene)
{}

const TiledEntity* TiledEntities::FindEntityWithType(const std::string& aType)
{
	for (const auto& entity : myParser->myResult->GetEntities())
	{
		if (entity.GetType() == aType)
		{
			return &entity;
		}
	}

	return nullptr;
}

void TiledEntities::SpawnEntities()
{
	for (const auto& entity : myParser->myResult->GetEntities())
	{
		const std::string& type = entity.GetType();

		if (type == "Enemy")
		{
			EnemyMessageData enemyMessageData{};
			enemyMessageData.mySpawnPosition = entity.GetPosition();

			if (entity.GetSubType() == "Zombie")
			{
				enemyMessageData.myEnemyType = EnemyFactory::EnemyType::Zombie;
			}
			else if (entity.GetSubType() == "EliteZombie")
			{
				enemyMessageData.myEnemyType = EnemyFactory::EnemyType::EliteZombie;
			}
			else
			{
				assert(false && "Invalid enemy subtype!");
			}

			if (entity.HasProperty("Loot"))
			{
				if (entity.GetProperty("Loot") == "Berserk")
				{
					enemyMessageData.myLootType = PowerUpType::Berserk;
				}
				if (entity.GetProperty("Loot") == "SniperShot")
				{
					enemyMessageData.myLootType = PowerUpType::SniperShot;
				}
				if (entity.GetProperty("Loot") == "HealthPickup")
				{
					enemyMessageData.myLootType = PowerUpType::HealthPickup;
				}
			}

			myScene->GetGlobalServiceProvider()->GetGameMessenger()->Send(GameMessage::SpawnEnemy, &enemyMessageData);
		}
		
		if (type == "DialogBox")
		{
			std::shared_ptr<DialogueBox> textbox = std::make_shared<DialogueBox>(myScene);
			textbox->Init(entity.GetProperty("DialogID"));
			textbox->SetPosition(entity.GetPosition());
			myScene->AddGameObject(textbox);
		}
	}
}
