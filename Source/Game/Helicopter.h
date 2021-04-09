#pragma once

#include "GameObject.h"

class SpriteSheetAnimation;

class Helicopter :
	public GameObject
{
public:

	Helicopter(Scene* aScene);

	virtual void Init() override;
	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;

private:

	std::unique_ptr<SpriteSheetAnimation> myAnimation;

};
