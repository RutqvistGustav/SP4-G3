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
}

ParallaxLayer::~ParallaxLayer() = default;

void ParallaxLayer::Update(const CU::Vector2<float>& aCameraOffset)
{
	myFinalRenderOffset = myLayerOffset + (aCameraOffset - myOrigin) * -mySpeedFactor;

	if (ShouldRepeatHorizontal()) myFinalRenderOffset.x = std::fmodf(myFinalRenderOffset.x, mySprite->GetSize().x);
	if (ShouldRepeatVertical()) myFinalRenderOffset.y = std::fmodf(myFinalRenderOffset.y, mySprite->GetSize().y);
}

void ParallaxLayer::Render(RenderQueue* const aRenderQueue)
{
	constexpr float threshold = 1.0f;

	const bool renderHorizontalExtent = ShouldRepeatHorizontal() && (std::abs(myFinalRenderOffset.x) >= threshold);
	const bool renderVerticalExtent = ShouldRepeatVertical() && (std::abs(myFinalRenderOffset.y) >= threshold);

	{
		SetupSpriteForPart({ 0.0f, 0.0f });

		aRenderQueue->Queue(RenderCommand(mySprite));
	}

	if (renderHorizontalExtent)
	{
		SetupSpriteForPart({ static_cast<float>(MathHelper::Signum(myFinalRenderOffset.x)), 0.0f });

		aRenderQueue->Queue(RenderCommand(mySprite));
	}

	if (renderVerticalExtent)
	{
		SetupSpriteForPart({ 0.0f, static_cast<float>(MathHelper::Signum(myFinalRenderOffset.y)) });

		aRenderQueue->Queue(RenderCommand(mySprite));
	}

	if (renderHorizontalExtent && renderVerticalExtent)
	{
		SetupSpriteForPart({ static_cast<float>(MathHelper::Signum(myFinalRenderOffset.x)), static_cast<float>(MathHelper::Signum(myFinalRenderOffset.y)) });

		aRenderQueue->Queue(RenderCommand(mySprite));
	}
}

void ParallaxLayer::SetLayerOffset(const CU::Vector2<float>& anOffset)
{
	myLayerOffset = anOffset;
}

const CU::Vector2<float>& ParallaxLayer::GetLayerOffset() const
{
	return myLayerOffset;
}

ParallaxLayer& ParallaxLayer::SetRepeatBehaviour(RepeatBehaviour aRepeatBehaviour)
{
	myRepeatBehaviour = aRepeatBehaviour;

	return *this;
}

ParallaxLayer& ParallaxLayer::SetOrigin(const CU::Vector2<float>& anOrigin)
{
	myOrigin = anOrigin;

	return *this;
}

void ParallaxLayer::SetupSpriteForPart(const CU::Vector2<float>& aDirection)
{
	const CU::Vector2<float> referenceSize = mySprite->GetSize();

	const CU::Vector2<float> center = referenceSize * 0.5f;
	const CU::Vector2<float> partOffset = { -aDirection.x * referenceSize.x, -aDirection.y * referenceSize.y };

	mySprite->SetPosition(center + partOffset + myFinalRenderOffset);
}

bool ParallaxLayer::ShouldRepeatHorizontal() const
{
	return (static_cast<int>(myRepeatBehaviour) & static_cast<int>(RepeatBehaviour::Horizontal)) > 0;
}

bool ParallaxLayer::ShouldRepeatVertical() const
{
	return (static_cast<int>(myRepeatBehaviour) & static_cast<int>(RepeatBehaviour::Vertical)) > 0;
}
