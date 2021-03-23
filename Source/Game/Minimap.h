#pragma once

#include "AABB.h"

class DynamicTexture;
class TiledCollision;
class TiledParser;
class SpriteWrapper;
class RenderQueue;

class Minimap
{
public:

	Minimap(TiledParser* aTiledParser, TiledCollision* aTiledCollision);
	~Minimap();

	void Update(float aDeltaTime);
	void Render(RenderQueue* const aRenderQueue);

	void SetGameView(const AABB& aGameView);
	void SetUIView(const AABB& aUIView);

private:

	void UpdateTexture();
	void UpdateView();

private:

	TiledParser* myTiledParser;
	TiledCollision* myTiledCollision;

	std::unique_ptr<DynamicTexture> myMapTexture;
	std::shared_ptr<SpriteWrapper> myMapSprite;

	AABB myGameView;
	AABB myUIView;

};
