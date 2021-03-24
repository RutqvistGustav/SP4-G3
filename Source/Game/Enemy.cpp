#include "stdafx.h"
#include "Enemy.h"
#include "Scene.h"
#include "Health.h"

Enemy::Enemy(Scene* aScene)
	: GameObject(aScene)
{		
}
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

const int Enemy::DealDamage()
{
	return myDamage;
}

void Enemy::TakeDamage(const int aDamage)
{
	myHealth->TakeDamage(aDamage);
	myDeleteThisFrame = myHealth->IsDead();
}

void Enemy::SetTarget(std::shared_ptr<GameObject> aTarget)
{
	myTarget = aTarget;
}
