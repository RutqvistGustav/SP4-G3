#include "stdafx.h"
#include "ParallaxContainer.h"

#include "Scene.h"

ParallaxContainer::ParallaxContainer(Scene* aScene) :
	myScene(aScene)
{}

ParallaxContainer::~ParallaxContainer() = default;

void ParallaxContainer::Update(const float aDeltaTime)
{
	const CU::Vector2<float> parallaxOffset = (myScene->GetCamera()->GetPosition() - myOrigin) * -1.0f;

	for (auto& layer : myLayers)
	{
		layer.Update(aDeltaTime, parallaxOffset);
	}
}

void ParallaxContainer::Render(RenderQueue* const aRenderQueue)
{
	for (auto& layer : myLayers)
	{
		layer.Render(aRenderQueue);
	}
}

void ParallaxContainer::AddLayer(const float aSpeed, GameLayer::Layer aLayer, const std::string& aSpritePath)
{
	myLayers.emplace_back(myScene, aSpeed, aLayer, aSpritePath);
}

void ParallaxContainer::SetParallaxOrigin(const CU::Vector2<float>& anOrigin)
{
	myOrigin = anOrigin;
}
