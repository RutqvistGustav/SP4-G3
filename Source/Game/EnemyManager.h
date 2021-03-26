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

	void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	void AddEnemy(EnemyFactory::EnemyType anEnemyType, CU::Vector2<float> aPosition, std::shared_ptr<GameObject> aTarget);

	void AddTargetToAllEnemies(std::shared_ptr<GameObject> aTarget);

	GameMessageAction OnMessage(const GameMessage aMessage, const EnemyMessageData* someMessageData) override;

private:

	void DeleteMarkedEnemies();

private:

	std::vector<std::shared_ptr<Enemy>> myEnemies;
	Scene* myScene;

	Minimap* myMinimap;

};

