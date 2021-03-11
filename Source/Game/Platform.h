#pragma once
#include "GameObject.h"
class Platform : public GameObject
{
public:
	Platform(Scene* aScene, const char* aSpritePath);
	~Platform();

	void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
	void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);
private:
};

