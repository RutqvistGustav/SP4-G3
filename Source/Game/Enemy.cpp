#include "stdafx.h"
#include "Enemy.h"
#include "Scene.h"

Enemy::Enemy(Scene* aScene, const char* aSpritePath)
	: GameObject(aScene, GameObjectTag::Enemy, aSpritePath)
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

void Enemy::SetTarget(std::shared_ptr<GameObject> aTarget)
{
	myTarget = aTarget;
}
