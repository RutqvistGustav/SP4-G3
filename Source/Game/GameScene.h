#pragma once

#include "CheckpointContext.h"
#include "Scene.h"

#include <memory>

class Player;
class SpriteWrapper;
class Enemy;
class EnemyManager;

class TiledParser;
class TiledRenderer;
class TiledCollision;
class TiledEntities;

class Minimap;

class GameScene : public Scene
{
public:

	GameScene();
	virtual ~GameScene() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:

	CheckpointContext SaveCheckpoint();
	void LoadCheckpoint(CheckpointContext& aCheckpointContext);

private:
	std::shared_ptr<SpriteWrapper> myTga2dLogoSprite;

	std::shared_ptr<Player> myPlayer;

	std::unique_ptr<EnemyManager> myEnemyManager;

	std::unique_ptr<TiledParser> myTiledParser;
	std::unique_ptr<TiledRenderer> myTiledRenderer;
	std::unique_ptr<TiledCollision> myTiledCollision;
	std::unique_ptr<TiledEntities> myTiledEntities;

	std::unique_ptr<Minimap> myMinimap;

};
