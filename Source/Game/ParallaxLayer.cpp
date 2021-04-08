#include "stdafx.h"
#include "ParallaxLayer.h"

#include "MathHelper.h"
#include "Metrics.h"

#include "SpriteWrapper.h"

#include "RenderCommand.h"
#include "RenderQueue.h"

#include "MathHelper.h"

#include <cassert>

ParallaxLayer::ParallaxLayer(Scene* aScene, const float aSpeedFactor, const GameLayer::Layer aLayer, const std::string& aSpritePath) :
	myScene(aScene),
	mySpeedFactor(aSpeedFactor),
	myLayer(aLayer),
	mySpritePath(aSpritePath)
{
	mySprite = std::make_shared<SpriteWrapper>(mySpritePath);
	mySprite->SetPanStrengthFactor(0.0f);
	mySprite->SetLayer(aLayer);

	const CU::Vector2<float> textureSize = mySprite->GetSize();

	const float endU = Metrics::GetReferenceSize().x / textureSize.x;
	const float endV = Metrics::GetReferenceSize().y / textureSize.y;

	assert(endU > 0.0f && endU <= 1.0f && "Invalid parallax layer texture dimensions");
	assert(endV > 0.0f && endV <= 1.0f && "Invalid parallax layer texture dimensions");

	mySprite->SetTextureRect({ 0.0f, 0.0f, MathHelper::Clamp(endU, 0.0f, 1.0f), MathHelper::Clamp(endV, 0.0f, 1.0f) });
	mySprite->SetSize(Metrics::GetReferenceSize());
}

ParallaxLayer::~ParallaxLayer() = default;

void ParallaxLayer::Update(const float aDeltaTime, const CU::Vector2<float>& anOffset)
{
	myLayerOffset = anOffset * mySpeedFactor;

	myLayerOffset.x = std::fmodf(myLayerOffset.x, Metrics::GetReferenceSize().x);
	myLayerOffset.y = std::fmodf(myLayerOffset.y, Metrics::GetReferenceSize().y);
}

void ParallaxLayer::Render(RenderQueue* const aRenderQueue)
{
	constexpr float threshold = 1.0f;

	const bool renderHorizontalExtent = std::abs(myLayerOffset.x) >= threshold;
	const bool renderVerticalExtent = std::abs(myLayerOffset.y) >= threshold;

	{
		SetupSpriteForPart({ 0.0f, 0.0f });

		aRenderQueue->Queue(RenderCommand(mySprite));
	}

	if (renderHorizontalExtent)
	{
		SetupSpriteForPart({ static_cast<float>(MathHelper::Signum(myLayerOffset.x)), 0.0f });

		aRenderQueue->Queue(RenderCommand(mySprite));
	}

	if (renderVerticalExtent)
	{
		SetupSpriteForPart({ 0.0f, static_cast<float>(MathHelper::Signum(myLayerOffset.y)) });

		aRenderQueue->Queue(RenderCommand(mySprite));
	}

	if (renderHorizontalExtent && renderVerticalExtent)
	{
		SetupSpriteForPart({ static_cast<float>(MathHelper::Signum(myLayerOffset.x)), static_cast<float>(MathHelper::Signum(myLayerOffset.y)) });

		aRenderQueue->Queue(RenderCommand(mySprite));
	}
}

void ParallaxLayer::SetupSpriteForPart(const CU::Vector2<float>& aDirection)
{
	const CU::Vector2<float> referenceSize = Metrics::GetReferenceSize();

	const CU::Vector2<float> center = referenceSize * 0.5f;
	const CU::Vector2<float> partOffset = { -aDirection.x * referenceSize.x, -aDirection.y * referenceSize.y };

	mySprite->SetPosition(center + partOffset + myLayerOffset);
}
