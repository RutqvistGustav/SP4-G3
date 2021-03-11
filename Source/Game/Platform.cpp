#include "stdafx.h"
#include "Platform.h"

#include "RenderCommand.h"
#include "RenderQueue.h"


//TODO: Add Tiled Reading of position, Sprite, and Collider.
Platform::Platform(Scene* aScene, const char* aSpritePath)
	: GameObject(aScene, aSpritePath)
{}

void Platform::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
}

void Platform::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	GameObject::Render(aRenderQueue, aRenderContext);
}
