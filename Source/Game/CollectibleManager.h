#pragma once
#include "EnemyDeathMessage.h"
#include <vector>
#include "CheckpointMessage.h"
#include "CheckpointObjectData.h"
#include "PowerUpType.h"
#include "CollectableMessage.h"

class Scene;
class Collectable;

class CollectibleManager :
	public IGameMessageSubscriber
{
public:
	CollectibleManager(Scene* aScene);
	~CollectibleManager();

	void AddCollectible(const PowerUpType aCollectibleType, const CU::Vector2<float> aSpawnPosition);

	GameMessageAction OnMessage(const GameMessage aMessage, const EnemyDeathMessageData* someMessageData);

	void DeleteMarkedCollectables();
	void DeleteAllCollectables();

private:
	struct CollectableCheckpointData : public CheckpointObjectData
	{
		struct CollectableData
		{
			CU::Vector2<float> myPosition;
			PowerUpType myPowerupType;
		};

		std::vector<CollectableData> mySavedCollectables;
	};

	GameMessageAction OnMessage(const GameMessage aMessage, const CheckpointMessageData* someMessageData);
	GameMessageAction OnMessage(const GameMessage aMessage, const CollectableMessageData* someMessageData);
	virtual GameMessageAction OnMessage(const GameMessage aMessage, const void* someMessageData) override;

private:
	Scene* myScene;
	std::vector<std::shared_ptr<Collectable>> myCollectibles;
};

