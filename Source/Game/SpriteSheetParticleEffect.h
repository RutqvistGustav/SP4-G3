#pragma once

#include "GameObject.h"

class SpriteSheetAnimation;

class SpriteSheetParticleEffect :
	public GameObject
{
public:

	SpriteSheetParticleEffect(Scene* aScene, const std::string& anAnimationPath);

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;

	void SetRotation(float aRotation);

private:

	std::unique_ptr<SpriteSheetAnimation> myAnimation;

};
