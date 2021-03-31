#include "stdafx.h"
#include "CollectibleManager.h"
#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "GameMessenger.h"
#include "EnemyDeathMessage.h"
#include "PowerUp.h"
#include "HealthPickup.h"

CollectibleManager::CollectibleManager(Scene* aScene) : 
	myScene(aScene)
{
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::EnemyDied, this);
}

CollectibleManager::~CollectibleManager()
{
	myScene->GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::EnemyDied, this);
}

void CollectibleManager::AddCollectible(const PowerUpType aCollectibleType, const CU::Vector2<float> aSpawnPosition)
{
	return; // temp
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
		std::shared_ptr<HealthPickup> healthPickup = std::make_shared<HealthPickup>(myScene);
		healthPickup->SetPosition(aSpawnPosition);
		myCollectibles.push_back(healthPickup);
		myScene->AddGameObject(healthPickup);
	}
		break;
	default:
		break;
	}
}

GameMessageAction CollectibleManager::OnMessage(const GameMessage aMessage, const EnemyDeathMessageData* someMessageData)
{
	AddCollectible(someMessageData->myLootType, someMessageData->myDeathPosition);
	return GameMessageAction::Keep;
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


