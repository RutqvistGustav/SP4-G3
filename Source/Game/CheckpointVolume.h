#pragma once

#include "TriggerVolume.h"

class SpriteSheetAnimation;

class CheckpointVolume :
	public TriggerVolume
{
public:

	CheckpointVolume(Scene* aScene);

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;
	virtual void TriggerEnter(GameObject* aGameObject) override;

private:

	bool myIsUsed{};

	std::unique_ptr<SpriteSheetAnimation> myAnimation;
};
