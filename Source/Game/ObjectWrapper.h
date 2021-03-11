#pragma once

#include "GameLayer.h"

class ObjectWrapper
{
public:

	virtual ~ObjectWrapper() = default;

	inline void SetLayer(GameLayer::Layer aLayer) { myLayer = aLayer; }
	inline GameLayer::Layer GetLayer() const { return myLayer; }

	inline void SetPanStrengthFactor(const float aPanStrengthFactor) { myPanStrengthFactor = aPanStrengthFactor; }
	inline float GetPanStrengthFactor() const { return myPanStrengthFactor; }

private:

	GameLayer::Layer myLayer{};
	float myPanStrengthFactor{ 1.0f };

};