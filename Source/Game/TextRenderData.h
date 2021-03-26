#pragma once

#include "Vector2.hpp"

#include <tga2d/math/color.h>
#include <tga2d/text/text.h>

struct TextRenderData
{
	TextRenderData() = default;
	~TextRenderData() = default;

	CommonUtilities::Vector2<float> myPosition;

	float myScale{};
	float myRotation{};

	Tga2D::CColor myColor{ 1.0f, 1.0f, 1.0f, 1.0f };

	std::string myText;

	std::string myPathAndName;
	Tga2D::EFontSize myFontSize;
	unsigned char myBorderSize;
};
