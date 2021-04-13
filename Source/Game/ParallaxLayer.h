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

	enum class RepeatBehaviour
	{
		Horizontal = (1 << 0),
		Vertical   = (1 << 1),

		All = Horizontal | Vertical,
	};

	ParallaxLayer(Scene* aScene, const float aSpeedFactor, const GameLayer::Layer aLayer, const std::string& aSpritePath);
	~ParallaxLayer();

	void Update(const CU::Vector2<float>& aCameraOffset);
	void Render(RenderQueue* const aRenderQueue);

	void SetLayerOffset(const CU::Vector2<float> &anOffset);
	const CU::Vector2<float>& GetLayerOffset() const;

	ParallaxLayer& SetRepeatBehaviour(RepeatBehaviour aRepeatBehaviour);
	ParallaxLayer& SetOrigin(const CU::Vector2<float>& anOrigin);

private:

	void SetupSpriteForPart(const CU::Vector2<float>& aDirection);

	bool ShouldRepeatHorizontal() const;
	bool ShouldRepeatVertical() const;

private:

	Scene* myScene;

	RepeatBehaviour myRepeatBehaviour{ RepeatBehaviour::All };

	CU::Vector2<float> myOrigin;

	float mySpeedFactor;
	GameLayer::Layer myLayer;

	const std::string mySpritePath;

	CU::Vector2<float> myLayerOffset;

	CU::Vector2<float> myFinalRenderOffset;
	std::shared_ptr<SpriteWrapper> mySprite;

};
