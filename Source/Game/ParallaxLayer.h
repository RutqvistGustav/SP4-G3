#pragma once

#include "GameLayer.h"

#include "Vector2.hpp"

class RenderQueue;
class Scene;
class SpriteWrapper;

/// <summary>
/// NOTE: All layer sprites need to be 1920x1080!
/// </summary>
class ParallaxLayer
{
public:

	ParallaxLayer(Scene* aScene, const float aSpeedFactor, const GameLayer::Layer aLayer, const std::string& aSpritePath);
	~ParallaxLayer();

	void Update(const float aDeltaTime, const CU::Vector2<float>& anOffset);
	void Render(RenderQueue* const aRenderQueue);

private:

	void SetupSpriteForPart(const CU::Vector2<float>& aDirection);

private:

	Scene* myScene;

	float mySpeedFactor;
	GameLayer::Layer myLayer;

	const std::string mySpritePath;

	CU::Vector2<float> myLayerOffset;
	std::shared_ptr<SpriteWrapper> mySprite;

};
