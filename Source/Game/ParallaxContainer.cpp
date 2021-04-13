#include "stdafx.h"
#include "ParallaxContainer.h"

#include "Scene.h"

ParallaxContainer::ParallaxContainer(Scene* aScene) :
	myScene(aScene)
{
	myScene->GetCamera()->Subscribe(this);
}

ParallaxContainer::~ParallaxContainer()
{
	myScene->GetCamera()->Unsubscribe(this);
}

void ParallaxContainer::Render(RenderQueue* const aRenderQueue)
{
	for (auto& layer : myLayers)
	{
		layer.Render(aRenderQueue);
	}
}

ParallaxLayer& ParallaxContainer::AddLayer(const float aSpeed, GameLayer::Layer aLayer, const std::string& aSpritePath)
{
	return myLayers.emplace_back(myScene, aSpeed, aLayer, aSpritePath);
}

ParallaxLayer* ParallaxContainer::GetLayer(int anIndex)
{
	return &myLayers[anIndex];
}

void ParallaxContainer::UpdateLayers()
{
	const CU::Vector2<float> cameraPosition = myScene->GetCamera()->GetPosition();

	for (auto& layer : myLayers)
	{
		layer.Update(cameraPosition);
	}
}

void ParallaxContainer::OnEvent(CU::Vector2<float> someEventData)
{
	UpdateLayers();
}
