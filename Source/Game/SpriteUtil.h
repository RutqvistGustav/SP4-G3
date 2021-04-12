#pragma once

#include "Vector2.hpp"

#include "SpriteWrapper.h"

#include <memory>

namespace SpriteUtil
{

	static void SetSpriteRect(std::shared_ptr<SpriteWrapper>& aSprite, const CU::Vector2<float>& aSize, const CU::Vector2<float>& aPivot = { 0.5f, 0.5f })
	{
		const float ppx = 1.0f / aSprite->GetSize().x;
		const float ppy = 1.0f / aSprite->GetSize().y;

		const float overshootX = (aSprite->GetSize().x - aSize.x);
		const float overshootY = (aSprite->GetSize().y - aSize.y);

		aSprite->SetTextureRect({ aPivot.x * overshootX * ppx, aPivot.y * overshootY * ppy, 1.0f - overshootX * ppx * (1.0f - aPivot.x), 1.0f - overshootY * ppy * (1.0f - aPivot.y) });
		aSprite->SetSize(aSize);
	}

}