#pragma once

#include "Scene.h"

#include "StageClearMessage.h"

#include <array>
#include <memory>

class Player;
class SpriteWrapper;
class Enemy;
class EnemyManager;
class CollectibleManager;

class ParticleEffectManager;

class ParallaxContainer;
class ParallaxLayer;

class TiledParser;
class TiledRenderer;
class TiledCollision;
class TiledEntities;

class DialogueBox;
class PauseMenu;

class GameScene :
	public Scene,
	public StageClearMessage
{
public:

	GameScene(const std::string& aMapPath);
	virtual ~GameScene() override;

	virtual void Init() override;

	virtual void OnExit() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:

	virtual GameMessageAction OnMessage(const GameMessage aMessage, const StageClearMessageData* someMessageData) override;

	void UpdateCustomParallaxEffects(float aDeltaTime);
	void CheckOutOfBounds();

	void StartPauseMenu(UpdateContext& anUpdateContext);
	void StopPauseMenu();

private:
	bool myIsGamePaused = false;

	const std::string myMapPath;

	AABB myMapAABB;

	std::shared_ptr<Player> myPlayer;

	std::unique_ptr<EnemyManager> myEnemyManager;
	std::unique_ptr<CollectibleManager> myCollectibleManager;
	std::unique_ptr<ParticleEffectManager> myParticleEffectManager;

	std::unique_ptr<TiledParser> myTiledParser;
	std::unique_ptr<TiledRenderer> myTiledRenderer;
	std::unique_ptr<TiledCollision> myTiledCollision;
	std::unique_ptr<TiledEntities> myTiledEntities;

	float myParallaxDustRotation{};
	std::array<ParallaxLayer*, 2> myParallaxDustLayers{};
	std::unique_ptr<ParallaxContainer> myParallaxContainer;

	std::unique_ptr<PauseMenu> myPauseMenu;
};
