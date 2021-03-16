#include "stdafx.h"
#include "Enemy.h"
#include "Scene.h"

Enemy::Enemy(Scene* aScene, const char* aSpritePath)
	: GameObject(aScene, aSpritePath)
{
}

Enemy::~Enemy()
{
}

void Enemy::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
}

void Enemy::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
}
