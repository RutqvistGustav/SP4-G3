#pragma once
#include "EnemyMessage.h"
#include <vector>
#include <memory>

struct UpdateContext;
struct RenderContext;
class RenderQueue;
class Enemy;
class EnemyFactory;
	
class EnemyManager : public EnemyMessage
{
public:
	EnemyManager(Scene* aScene);
	~EnemyManager();

	void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	void AddEnemy(EnemyFactory::EnemyType anEnemyType, CU::Vector2<float> aPosition);

	GameMessageAction OnMessage(const GameMessage aMessage, const EnemyMessageData* someMessageData) override;
private:

	void DeleteMarkedEnemies();

	std::vector<std::shared_ptr<Enemy>> myEnemies;
	Scene* myScene;
};

