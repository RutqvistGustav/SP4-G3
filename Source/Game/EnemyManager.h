#pragma once
#include "EnemyMessage.h"
#include <vector>
#include <memory>

struct UpdateContext;
struct RenderContext;
class RenderQueue;
class Enemy;
class EnemyFactory;

class Minimap;

class EnemyManager : public EnemyMessage
{
public:

	EnemyManager(Scene* aScene, Minimap* aMinimap);
	~EnemyManager();

	void AddEnemy(EnemyFactory::EnemyType anEnemyType, CU::Vector2<float> aPosition, std::shared_ptr<GameObject> aTarget, const PowerUpType& aLootType);

	void AddTargetToAllEnemies(std::shared_ptr<GameObject> aTarget);

	void SendDeathMessage(const PowerUpType aLootType, const CU::Vector2<float> aSpawnPosition);

	GameMessageAction OnMessage(const GameMessage aMessage, const EnemyMessageData* someMessageData) override;

	void DeleteMarkedEnemies();
private:


private:

	std::vector<std::shared_ptr<Enemy>> myEnemies;
	Scene* myScene;

	Minimap* myMinimap;

};

