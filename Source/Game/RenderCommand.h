#pragma once

#include "GameLayer.h"

#include "RenderObjectType.h"
#include "SpriteRenderData.h"

class SpriteWrapper;

class RenderCommand
{
public:

	RenderCommand(const std::shared_ptr<SpriteWrapper> aSprite);
	~RenderCommand();

private:

	RenderCommand();

	void Init(const std::shared_ptr<SpriteWrapper> aSprite);

	void Reset();

private:

	friend class RenderManager;

	RenderObjectType myType{ RenderObjectType::Unknown };
	GameLayer::Layer myLayer{};
	float myPanStrengthFactor{ 1.0f };

	union
	{
		SpriteRenderData mySpriteRenderData;
	};

};
