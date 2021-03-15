#pragma once

#include "GameLayer.h"

#include "RenderObjectType.h"

#include "SpriteRenderData.h"
#include "SpriteBatchRenderData.h"

#include <memory>

class SpriteBatchWrapper;
class SpriteWrapper;

class RenderCommand
{
public:

	RenderCommand(const std::shared_ptr<SpriteWrapper> aSprite);
	RenderCommand(const std::shared_ptr<SpriteBatchWrapper> aSpriteBatch);

	RenderCommand(const RenderCommand& anOther);
	RenderCommand(RenderCommand&& anOther);

	~RenderCommand();

	RenderCommand& operator=(const RenderCommand& anOther);
	RenderCommand& operator=(RenderCommand&& anOther);

private:

	RenderCommand();

	void Init(const std::shared_ptr<SpriteWrapper> aSprite);
	void Init(const std::shared_ptr<SpriteBatchWrapper> aSpriteBatch);

	void CopyFrom(const RenderCommand& anOther);
	void MoveFrom(RenderCommand&& anOther);

	void Reset();

private:

	friend class RenderManager;

	RenderObjectType myType{ RenderObjectType::Unknown };
	GameLayer::Layer myLayer{};
	float myPanStrengthFactor{ 1.0f };

	union
	{
		SpriteRenderData mySpriteRenderData;
		SpriteBatchRenderData mySpriteBatchRenderData;
	};

};
