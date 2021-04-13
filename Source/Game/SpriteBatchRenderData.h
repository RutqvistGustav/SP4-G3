#pragma once

#include "SpriteRenderData.h"

#include <vector>

struct SpriteBatchRenderData : public BaseRenderData
{
	Tga2D::CTexture* myTexture{};
	std::vector<SpriteRenderData> mySprites;
};
