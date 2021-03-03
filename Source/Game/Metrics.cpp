#include "stdafx.h"

#include "Metrics.h"

namespace Metrics
{
	static const CommonUtilities::Vector2<float> locReferenceSize = { 1920.0f, 1080.0f };

	CommonUtilities::Vector2<float> GetRenderSize()
	{
		const VECTOR2UI renderSize = Tga2D::CEngine::GetInstance()->GetRenderSize();

		return { static_cast<float>(renderSize.myX), static_cast<float>(renderSize.myY) };
	}

	CommonUtilities::Vector2<float> GetReferenceSize()
	{
		return locReferenceSize;
	}
}
