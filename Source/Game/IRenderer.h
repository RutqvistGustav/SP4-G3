#pragma once

#include "Vector2.hpp"

#include <memory>
#include <vector>

struct ExtraRenderInformation
{
	CU::Vector2<float> myOffset;
};

struct SpriteRenderData;
struct SpriteBatchRenderData;

class IRenderer
{
public:

	virtual ~IRenderer() = 0 {}

	virtual void Render(const SpriteRenderData& aSprite, const ExtraRenderInformation& someExtraInformation) = 0;
	virtual void Render(const SpriteBatchRenderData& aSpriteBatch, const ExtraRenderInformation& someExtraInformation) = 0;

};