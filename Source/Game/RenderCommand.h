#pragma once

#include "GameLayer.h"

#include "RenderObjectType.h"

#include "SpriteRenderData.h"
#include "SpriteBatchRenderData.h"

#include <tga2d/text/text.h>

#include <memory>

class SpriteBatchWrapper;
class SpriteWrapper;
class TextWrapper;

class RenderCommand
{
public:

	RenderCommand(const std::shared_ptr<SpriteWrapper> aSprite);
	RenderCommand(const std::shared_ptr<SpriteBatchWrapper> aSpriteBatch);
	RenderCommand(const std::shared_ptr<TextWrapper> aText);

	RenderCommand(const RenderCommand& anOther);
	RenderCommand(RenderCommand&& anOther) noexcept;

	~RenderCommand();

	RenderCommand& operator=(const RenderCommand& anOther);
	RenderCommand& operator=(RenderCommand&& anOther);

private:

	RenderCommand();

	void Init(const std::shared_ptr<SpriteWrapper> aSprite);
	void Init(const std::shared_ptr<SpriteBatchWrapper> aSpriteBatch);
	void Init(const std::shared_ptr<TextWrapper> aText);

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
		Tga2D::CText myText;
	};

};
