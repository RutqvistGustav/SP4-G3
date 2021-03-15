#pragma once

#include "Scene.h"

#include <memory>

class Player;
class SpriteWrapper;

class TiledParser;
class TiledRenderer;
class TiledCollision;

class GameScene : public Scene
{
public:

	GameScene();
	virtual ~GameScene() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:

	std::shared_ptr<SpriteWrapper> myTga2dLogoSprite;

	std::unique_ptr<Player> myPlayer;

	std::unique_ptr<TiledParser> myTiledParser;
	std::unique_ptr<TiledRenderer> myTiledRenderer;
	std::unique_ptr<TiledCollision> myTiledCollision;

};
