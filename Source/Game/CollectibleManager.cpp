#include "stdafx.h"
#include "CollectibleManager.h"
#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "GameMessenger.h"
#include "EnemyDeathMessage.h"
#include "PowerUp.h"
#include "HealthPickup.h"
#include "Key.h"
#include "CheckpointContext.h"

CollectibleManager::CollectibleManager(Scene* aScene) : 
	myScene(aScene)
{
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::SpawnCollectable, this);
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::EnemyDied, this);
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::CheckpointSave, this);
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::CheckpointLoad, this);
}

CollectibleManager::~CollectibleManager()
{
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::SpawnCollectable, this);
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::EnemyDied, this);
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::CheckpointSave, this);
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::CheckpointLoad, this);
}

void CollectibleManager::AddCollectible(const PowerUpType aCollectibleType, const CU::Vector2<float> aSpawnPosition)
{
	switch (aCollectibleType)
	{
	case PowerUpType::Berserk:
	{
		std::shared_ptr<PowerUp> berzerk = std::make_shared<PowerUp>(myScene, aCollectibleType);
		berzerk->SetPosition(aSpawnPosition);
		myCollectibles.push_back(berzerk);
		myScene->AddGameObject(berzerk);
	}
		break;
	case PowerUpType::SniperShot:
	{
		std::shared_ptr<PowerUp> sniperShot = std::make_shared<PowerUp>(myScene, aCollectibleType);
		sniperShot->SetPosition(aSpawnPosition);
		myCollectibles.push_back(sniperShot);
		myScene->AddGameObject(sniperShot);
	}
		break;
	case PowerUpType::HealthPickup:
	{
		std::shared_ptr<HealthPickup> healthPickup = std::make_shared<HealthPickup>(myScene, aCollectibleType);
		healthPickup->SetPosition(aSpawnPosition);
		myCollectibles.push_back(healthPickup);
		myScene->AddGameObject(healthPickup);
	}
		break;
	case PowerUpType::Key:
	{
		std::shared_ptr<Key> keyPickup = std::make_shared<Key>(myScene, aCollectibleType);
		keyPickup->SetPosition(aSpawnPosition);
		myCollectibles.push_back(keyPickup);
		myScene->AddGameObject(keyPickup);
	}
		break;
	default:
		break;
	}
}

void CollectibleManager::DeleteMarkedCollectables()
{
	for (int collectableIndex = static_cast<int>(myCollectibles.size()) - 1; collectableIndex >= 0; collectableIndex--)
	{
		if (myCollectibles[collectableIndex]->GetDeleteThisFrame())
		{
			auto eraseIt = myCollectibles.begin() + collectableIndex;

			myCollectibles.erase(eraseIt);
		}
	}
}

void CollectibleManager::DeleteAllCollectables()
{
	for (auto& collectable : myCollectibles)
	{
		collectable->SetDeleteThisFrame();
	}
}

GameMessageAction CollectibleManager::OnEnemyDeathMessage(const GameMessage /*aMessage*/, const EnemyDeathMessageData* someMessageData)
{
	AddCollectible(someMessageData->myLootType, someMessageData->myDeathPosition);
	return GameMessageAction::Keep;
}

GameMessageAction CollectibleManager::OnCheckpointMessage(const GameMessage aMessage, const CheckpointMessageData* someMessageData)
{
	switch (aMessage)
	{
	case GameMessage::CheckpointSave:
	{
		CollectableCheckpointData* data = someMessageData->myCheckpointContext->NewData<CollectableCheckpointData>("CollectableManager");

		data->mySavedCollectables.reserve(myCollectibles.size());
		for (auto& collectable : myCollectibles)
		{
			data->mySavedCollectables.push_back({collectable->GetPosition(), collectable->GetType()});
		}
		break;
	}

	case GameMessage::CheckpointLoad:
	{
		DeleteAllCollectables();

		CollectableCheckpointData* data = someMessageData->myCheckpointContext->GetData<CollectableCheckpointData>("CollectableManager");

		for (auto& collectable : data->mySavedCollectables)
		{
			AddCollectible(collectable.myPowerupType, collectable.myPosition);
		}
		break;
	}

	default:
		assert(false);
		break;
	}

	return GameMessageAction::Keep;
}

GameMessageAction CollectibleManager::OnSpawnCollectableMessage(const GameMessage aMessage, const CollectableMessageData* someMessageData)
{
	AddCollectible(someMessageData->myLootType, someMessageData->mySpawnPosition);

	return GameMessageAction::Keep;
}

GameMessageAction CollectibleManager::OnMessage(const GameMessage aMessage, const void* someMessageData)
{
	switch (aMessage)
	{
	case GameMessage::CheckpointSave:
	case GameMessage::CheckpointLoad:
		return OnCheckpointMessage(aMessage, reinterpret_cast<const CheckpointMessageData*>(someMessageData));
		
	case GameMessage::SpawnCollectable:
		return OnSpawnCollectableMessage(aMessage, reinterpret_cast<const CollectableMessageData*>(someMessageData));

	case GameMessage::EnemyDied:
		return OnEnemyDeathMessage(aMessage, reinterpret_cast<const EnemyDeathMessageData*>(someMessageData));

	default:
		assert(false);
		break;
	}

	return GameMessageAction::Unsubscribe;
}


