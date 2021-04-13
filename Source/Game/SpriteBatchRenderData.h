#pragma once

#include "SpriteRenderData.h"

#include <vector>

struct SpriteBatchRenderData : public BaseRenderData
{
	SpriteBatchRenderData() = default;
	~SpriteBatchRenderData() = default;

	Tga2D::CTexture* myTexture{};
	std::vector<SpriteRenderData> mySprites;
};
