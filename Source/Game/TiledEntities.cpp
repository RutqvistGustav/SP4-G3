#include "stdafx.h"
#include "TiledEntities.h"

#include "TiledParser.h"

#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "GameMessenger.h"
#include "CollectableMessage.h"
#include "JsonManager.h"

#include "PowerUp.h"
#include "HealthPickup.h"

#include "EnemyMessage.h"

#include "DialogueBox.h"

#include "GoalZone.h"
#include "DamageVolume.h"
#include "CheckpointVolume.h"

#include "Helicopter.h"

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
				enemyMessageData.myEnemyType = EnemyType::Zombie;
			}
			else if (entity.GetSubType() == "EliteZombie")
			{
				enemyMessageData.myEnemyType = EnemyType::EliteZombie;
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
				else if (entity.GetProperty("Loot") == "SniperShot")
				{
					enemyMessageData.myLootType = PowerUpType::SniperShot;
				}
				else if (entity.GetProperty("Loot") == "HealthPickup")
				{
					enemyMessageData.myLootType = PowerUpType::HealthPickup;
				}
			}
			if (entity.HasProperty("ShouldRoam"))
			{
				enemyMessageData.myShouldRoam = entity.GetProperty("ShouldRoam") == "True";
			}

			myScene->GetGlobalServiceProvider()->GetGameMessenger()->Send(GameMessage::SpawnEnemy, &enemyMessageData);
		}
		else if (type == "DialogBox")
		{
			std::shared_ptr<DialogueBox> textbox = std::make_shared<DialogueBox>(myScene);
			textbox->Init(entity.GetProperty("DialogID"));
			textbox->SetTriggerSize(entity.GetSize());
			textbox->SetPosition(entity.GetPosition());

			myScene->AddGameObject(textbox);
		}
		else if (type == "Goal")
		{
			std::shared_ptr<GoalZone> goalZone = std::make_shared<GoalZone>(myScene);
			goalZone->Init();
			goalZone->SetPosition(entity.GetPosition());
			goalZone->SetTriggerSize(entity.GetSize());

			myScene->AddGameObject(goalZone);
		}
		else if (type == "Hazard")
		{
			const std::string subType = entity.HasProperty("SubType") ? entity.GetProperty("SubType") : "Default";
			const JsonData& data = GetEntityData(type)[subType];

			std::shared_ptr<DamageVolume> damageVolume = std::make_shared<DamageVolume>(myScene);
			damageVolume->InitWithJson(data);

			damageVolume->SetPosition(entity.GetPosition());
			damageVolume->SetTriggerSize(entity.GetSize());

			myScene->AddGameObject(damageVolume);
		}
		else if (type == "Checkpoint")
		{
			std::shared_ptr<CheckpointVolume> checkpointVolume = std::make_shared<CheckpointVolume>(myScene);

			checkpointVolume->SetPosition(entity.GetPosition());
			checkpointVolume->SetTriggerSize(entity.GetSize());
			checkpointVolume->Init();


			myScene->AddGameObject(checkpointVolume);
		}
		else if (type == "PickUp" && entity.HasProperty("SubType"))
		{
			CollectableMessageData collectableMessageData;
			if (entity.GetSubType() == "Berserk")
			{
				collectableMessageData.myLootType = PowerUpType::Berserk;
			}
			else if (entity.GetSubType() == "SniperShot")
			{
				collectableMessageData.myLootType = PowerUpType::SniperShot;
			}
			else if (entity.GetSubType() == "HealthPickup")
			{
				collectableMessageData.myLootType = PowerUpType::HealthPickup;
			}
			else if (entity.GetSubType() == "KeyPickup")
			{
				collectableMessageData.myLootType = PowerUpType::Key;
				collectableMessageData.myDialogID = entity.GetProperty("DialogID");
			}

			collectableMessageData.mySpawnPosition = entity.GetPosition();
			myScene->GetGlobalServiceProvider()->GetGameMessenger()->Send(GameMessage::SpawnCollectable, &collectableMessageData);
		}
		else if (type == "AnimatedProp")
		{
			std::shared_ptr<GameObject> prop;

			if (entity.GetSubType() == "Helicopter")
			{
				prop = std::make_shared<Helicopter>(myScene);
			}

			if (prop)
			{
				prop->Init();
				prop->SetPosition(entity.GetPosition());

				myScene->AddGameObject(prop);
			}
		}
	}
}

const JsonData& TiledEntities::GetEntityData(const std::string& aType)
{
	return myScene->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/Entities.json")[aType];
}
