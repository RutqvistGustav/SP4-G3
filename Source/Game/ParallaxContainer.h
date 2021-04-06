#pragma once

#include "ParallaxLayer.h"

#include "Vector2.hpp"

#include <vector>

class Scene;

class ParallaxContainer
{
public:

	ParallaxContainer(Scene* aScene);
	~ParallaxContainer();

	void Update(const float aDeltaTime);
	void Render(RenderQueue* const aRenderQueue);

	void AddLayer(const float aSpeed, GameLayer::Layer aLayer, const std::string& aSpritePath);

	void SetParallaxOrigin(const CU::Vector2<float>& anOrigin);

private:

	Scene* myScene;

	CU::Vector2<float> myOrigin;

	std::vector<ParallaxLayer> myLayers;

};
