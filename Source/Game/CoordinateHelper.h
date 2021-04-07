#pragma once

#include "Metrics.h"

#include <algorithm>

#include <tga2d/engine.h>
#include <tga2d/math/vector2.h>
#include <Vector2.hpp>

class CoordinateHelper
{
public:

	static CU::Vector2<float> GetWindowAreaSize()
	{
		RECT rect;
		GetWindowRect(*Tga2D::CEngine::GetInstance()->GetHWND(), &rect);

		return CU::Vector2<float>(static_cast<float>(rect.right - rect.left), static_cast<float>(rect.bottom - rect.top));
	}

	static CU::Vector2<float> GetClientAreaSize()
	{
		RECT rect;
		GetClientRect(*Tga2D::CEngine::GetInstance()->GetHWND(), &rect);

		return CU::Vector2<float>(static_cast<float>(rect.right - rect.left), static_cast<float>(rect.bottom - rect.top));
	}

	static CU::Vector2<float> GetWindowSize()
	{
		const VECTOR2UI windowSize = Tga2D::CEngine::GetInstance()->GetWindowSize();
		return CU::Vector2<float>(static_cast<float>(windowSize.x), static_cast<float>(windowSize.y));
	}

	static CU::Vector2<float> GetRenderSize()
	{
		const VECTOR2UI renderSize = Tga2D::CEngine::GetInstance()->GetRenderSize();
		return CU::Vector2<float>(static_cast<float>(renderSize.x), static_cast<float>(renderSize.y));
	}

	static CU::Vector2<float> GetClientPositionAsVirtual(CU::Vector2<float> aClientPosition)
	{
		const CU::Vector2<float> renderSize = GetRenderSize();
		const CU::Vector2<float> clientAreaSize = GetClientAreaSize();
		const CU::Vector2<float> referenceSize = Metrics::GetReferenceSize();

		const float paddingX = (clientAreaSize.x - renderSize.x) * 0.5f;
		const float paddingY = (clientAreaSize.y - renderSize.y) * 0.5f;

		const float percX = std::clamp((aClientPosition.x - paddingX) / renderSize.x, 0.0f, 1.0f);
		const float percY = std::clamp((aClientPosition.y - paddingY) / renderSize.y, 0.0f, 1.0f);

		return CU::Vector2<float>(referenceSize.x * percX, referenceSize.y * percY);
	}

	static CU::Vector2<float> ComputeContainSize(CU::Vector2<float> anOriginalSize)
	{
		const CU::Vector2<float> virtualSize = Metrics::GetReferenceSize();

		const float virtualAspect = virtualSize.x / virtualSize.y;
		const float originalAspect = anOriginalSize.x / anOriginalSize.y;

		CU::Vector2<float> resultSize;

		if (virtualAspect >= originalAspect)
		{
			resultSize.x = virtualSize.y * originalAspect;
			resultSize.y = virtualSize.y;
		}
		else
		{
			resultSize.x = virtualSize.x;
			resultSize.y = virtualSize.x / originalAspect;
		}

		return resultSize;
	}

	static CU::Vector2<float> ComputeContainSize(CU::Vector2<float> anOriginalSize, CU::Vector2<float> anReferenceSize)
	{
		const float referenceAspect = anReferenceSize.x / anReferenceSize.y;
		const float originalAspect = anOriginalSize.x / anOriginalSize.y;

		CU::Vector2<float> resultSize;

		if (referenceAspect >= originalAspect)
		{
			resultSize.x = anReferenceSize.y * originalAspect;
			resultSize.y = anReferenceSize.y;
		}
		else
		{
			resultSize.x = anReferenceSize.x;
			resultSize.y = anReferenceSize.x / originalAspect;
		}

		return resultSize;
	}

	static CU::Vector2<float> ComputeCoverSize(CU::Vector2<float> anOriginalSize)
	{
		const CU::Vector2<float> virtualSize = Metrics::GetReferenceSize();

		const float virtualAspect = virtualSize.x / virtualSize.y;
		const float originalAspect = anOriginalSize.x / anOriginalSize.y;

		CU::Vector2<float> resultSize;

		if (virtualAspect >= originalAspect)
		{
			resultSize.x = virtualSize.x;
			resultSize.y = virtualSize.x / originalAspect;
		}
		else
		{
			resultSize.x = virtualSize.y * originalAspect;
			resultSize.y = virtualSize.y;
		}

		return resultSize;
	}

};

