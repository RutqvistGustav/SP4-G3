#pragma once

#include "SpriteRenderData.h"

#include <vector>

struct SpriteBatchRenderData
{
	SpriteBatchRenderData() = default;
	~SpriteBatchRenderData() = default;

	Tga2D::CTexture* myTexture{};
	std::vector<SpriteRenderData> mySprites;
};
