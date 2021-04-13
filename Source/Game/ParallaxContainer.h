#pragma once

#include "ParallaxLayer.h"

#include "Vector2.hpp"

#include "SimpleEventObserver.h"

#include <vector>

class Scene;

class ParallaxContainer :
	public SimpleEventObserver<CU::Vector2<float>>
{
public:

	ParallaxContainer(Scene* aScene);
	~ParallaxContainer();

	void Render(RenderQueue* const aRenderQueue);

	ParallaxLayer& AddLayer(const float aSpeed, GameLayer::Layer aLayer, const std::string& aSpritePath);
	ParallaxLayer* GetLayer(int anIndex);

protected:

	void UpdateLayers();

	virtual void OnEvent(CU::Vector2<float> someEventData) override;

private:

	Scene* myScene;

	std::vector<ParallaxLayer> myLayers;

};
