#include "stdafx.h"
#include "Enemy.h"
#include "Scene.h"
#include "Health.h"
#include "GlobalServiceProvider.h"
#include "JsonManager.h"
#include <nlohmann/json.hpp>


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

void Enemy::InitEnemyJsonValues(std::string& aJsonPath)
{
	nlohmann::json data = GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/EnemyTypes.json");
	nlohmann::json zombieData = data.at(aJsonPath);
	myHealth = std::make_unique<Health>(zombieData.at("Health"));
	myHealth->SetInvincibilityTimer(zombieData.at("Invincibility"));
	myDamage = zombieData.at("Damage");
	mySpeed = zombieData.at("MovementSpeed");
	myMaxSpeed = zombieData.at("MaxSpeedCap");
	myDetectionRange = zombieData.at("DetectionRange");
	myKnockback = zombieData.at("KnockBack");
}

PowerUpType Enemy::GetLootType()
{
	return myLoot;
}

void Enemy::SetLootType(const PowerUpType aLootType)
{
	myLoot = aLootType;
}

void Enemy::SetTarget(std::shared_ptr<GameObject> aTarget)
{
	if (aTarget != nullptr)
	{
		myTarget = aTarget;
	}
}
