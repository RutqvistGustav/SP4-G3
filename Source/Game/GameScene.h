#pragma once

#include "Scene.h"

#include <memory>

class Player;
class SpriteWrapper;
class Enemy;
class EnemyManager;
class CollectibleManager;

class ParallaxContainer;

class TiledParser;
class TiledRenderer;
class TiledCollision;
class TiledEntities;

class Minimap;

class DialogueBox;
class PauseMenu;

class GameScene : public Scene
{
public:

	GameScene(const std::string& aMapPath);
	virtual ~GameScene() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:
	const std::string myMapPath;

	std::shared_ptr<Player> myPlayer;

	std::unique_ptr<EnemyManager> myEnemyManager;
	std::unique_ptr<CollectibleManager> myCollectibleManager;

	std::unique_ptr<TiledParser> myTiledParser;
	std::unique_ptr<TiledRenderer> myTiledRenderer;
	std::unique_ptr<TiledCollision> myTiledCollision;
	std::unique_ptr<TiledEntities> myTiledEntities;

	std::unique_ptr<ParallaxContainer> myParallaxContainer;
	std::unique_ptr<Minimap> myMinimap;

	std::unique_ptr<PauseMenu> myPauseMenu;
};
