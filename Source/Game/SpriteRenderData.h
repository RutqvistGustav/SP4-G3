#pragma once

#include "TextureRect.h"

#include "Vector2.hpp"

#include <tga2d/texture/texture.h>
#include <tga2d/math/color.h>

struct SpriteRenderData
{
	CommonUtilities::Vector2<float> myPosition;
	CommonUtilities::Vector2<float> myPivot{ 0.5f, 0.5f };
	CommonUtilities::Vector2<float> mySize;

	float myRotation{};

	Tga2D::CColor myColor{ 1.0f, 1.0f, 1.0f, 1.0f };

	Tga2D::CTexture* myTexture{};
	TextureRect myTextureRect{ 0.0f, 0.0f, 1.0f, 1.0f };
};
