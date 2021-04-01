#pragma once
#include "EnemyDeathMessage.h"
#include <vector>

class Scene;
class Collectable;

class CollectibleManager : public EnemyDeathMessage
{
public:
	CollectibleManager(Scene* aScene);
	~CollectibleManager();

	void AddCollectible(const PowerUpType aCollectibleType, const CU::Vector2<float> aSpawnPosition);

	virtual GameMessageAction OnMessage(const GameMessage aMessage, const EnemyDeathMessageData* someMessageData) override;

	void DeleteMarkedCollectables();

private:
	Scene* myScene;
	std::vector<std::shared_ptr<Collectable>> myCollectibles;
};

