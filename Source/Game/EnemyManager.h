#pragma once

#include "CheckpointMessage.h"
#include "CheckpointObjectData.h"
#include "EnemyMessage.h"

#include <vector>
#include <memory>

struct UpdateContext;
struct RenderContext;
class RenderQueue;
class Enemy;
class EnemyFactory;

class EnemyManager :
	public IGameMessageSubscriber
{
public:

	EnemyManager(Scene* aScene);
	~EnemyManager();

	void AddEnemy(EnemyType anEnemyType, CU::Vector2<float> aPosition, std::shared_ptr<GameObject> aTarget, const PowerUpType& aLootType);

	void AddTargetToAllEnemies(std::shared_ptr<GameObject> aTarget);

	void SendDeathMessage(const PowerUpType aLootType, const CU::Vector2<float> aSpawnPosition);

	void DeleteAllEnemies();
	void DeleteMarkedEnemies();

	virtual GameMessageAction OnMessage(const GameMessage aMessage, const void* someMessageData) override;

private:
	
	struct EnemyManagerCheckpointData : public CheckpointObjectData
	{
		struct EnemyData
		{
			CU::Vector2<float> myPosition;
			EnemyType myEnemyType;
			PowerUpType myPowerupType;
		};

		std::vector<EnemyData> myEnemies;
	};

	GameMessageAction OnMessage(const GameMessage aMessage, const CheckpointMessageData* someMessageData);
	GameMessageAction OnMessage(const GameMessage aMessage, const EnemyMessageData* someMessageData);

private:

	std::vector<std::shared_ptr<Enemy>> myEnemies;
	Scene* myScene;

};

