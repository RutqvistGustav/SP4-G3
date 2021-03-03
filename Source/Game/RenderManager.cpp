#include "stdafx.h"
#include "RenderManager.h"

#include "Metrics.h"

#include "RenderCommand.h"
#include "RenderQueue.h"

#include <algorithm>

#include <tga2d/sprite/sprite.h>

using Vector2f = CommonUtilities::Vector2<float>;

static inline VECTOR2F GetEngineVectorFromCU(const Vector2f aVector)
{
	return VECTOR2F(aVector.x, aVector.y);
}

static inline VECTOR2F NormalizePosition(const Vector2f aPosition)
{
	const Vector2f renderSize = Metrics::GetRenderSize();

	return { aPosition.x / renderSize.x, aPosition.y / renderSize.y };
}

static inline VECTOR2F NormalizeSize(const Vector2f aSize)
{
	const Vector2f renderSize = Metrics::GetRenderSize();

	// NOTE: y on both is correct
	return { aSize.x / renderSize.y, aSize.y / renderSize.y };
}

RenderManager::RenderManager()
{
	myUpdateQueue = std::make_unique<RenderQueue>();
	myRenderQueue = std::make_unique<RenderQueue>();

	myRenderSprite = std::make_unique<Tga2D::CSprite>();
}

RenderManager::~RenderManager() = default;

void RenderManager::Render()
{
	const CommonUtilities::Vector2<float> renderSize = Metrics::GetRenderSize();
	const CommonUtilities::Vector2<float> referenceSize = Metrics::GetReferenceSize();

	// NOTE: Assumes locked aspect ratio at referenceSize aspect
	const float scaleFactor = renderSize.y / referenceSize.y;

	std::vector<RenderCommand>& commands = myRenderQueue->myCommands;
	std::sort(commands.begin(), commands.end(), RenderManager::CommandSort);

	for (const RenderCommand& command : commands)
	{
		switch (command.myType)
		{
		case RenderObjectType::Sprite:
		{
			auto& data = command.mySpriteRenderData;

			// NOTE: Performance optimization
			// add SetTexture to Tga2D::CSprite to prevent lookup of texture
			myRenderSprite->SetTexture(data.myTexture);
			myRenderSprite->SetTextureRect(data.myTextureRect.myStartX, data.myTextureRect.myStartY, data.myTextureRect.myEndX, data.myTextureRect.myEndY);

			myRenderSprite->SetPosition(NormalizePosition(data.myPosition * scaleFactor));
			myRenderSprite->SetPivot(GetEngineVectorFromCU(data.myPivot));
			myRenderSprite->SetSizeRelativeToScreen(NormalizeSize(data.mySize * scaleFactor));
			myRenderSprite->SetRotation(data.myRotation);

			myRenderSprite->SetColor(data.myColor);

			myRenderSprite->Render();
		}

			break;

		default:
			assert(false && "Trying to render invalid command type!");
			break;
		}
	}
}

void RenderManager::OnPostFrameThreadSync()
{
	myRenderQueue->Clear();

	std::swap(myUpdateQueue, myRenderQueue);
}

bool RenderManager::CommandSort(const RenderCommand& aLhs, const RenderCommand& aRhs)
{
	return aLhs.myLayer < aRhs.myLayer;
}
