#pragma once

#include "GameLayer.h"

class ObjectWrapper
{
public:

	virtual ~ObjectWrapper() = default;

	inline void SetLayer(GameLayer::Layer aLayer) { myLayer = aLayer; }
	inline GameLayer::Layer GetLayer() const { return myLayer; }

private:

	GameLayer::Layer myLayer{};

};