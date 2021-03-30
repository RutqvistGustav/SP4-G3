#include "stdafx.h"
#include "Enemy.h"
#include "Scene.h"
#include "Health.h"
#include "GlobalServiceProvider.h"
#include "JsonManager.h"

#include "SpriteWrapper.h"

#include <nlohmann/json.hpp>


Enemy::Enemy(Scene* aScene, const char* aSpritePath)
	: GameObject(aScene, GameObjectTag::Enemy, aSpritePath)
{
}

Enemy::~Enemy() = default;

void Enemy::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myPhysicsController.Update(aDeltaTime);
	SetPosition(myPhysicsController.GetPosition());
}

void Enemy::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	GameObject::Render(aRenderQueue, aRenderContext);
}

void Enemy::ApplyForce(const CU::Vector2<float>& aForce)
{
	myPhysicsController.ApplyForce(aForce);
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

void Enemy::InitEnemyJsonValues(const std::string& aJsonPath)
{
	nlohmann::json data = GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("JSON/EnemyTypes.json");
	nlohmann::json zombieData = data.at("EliteZombie");
	myHealth = std::make_unique<Health>(zombieData.at("Health"));
	myHealth->SetInvincibilityTimer(zombieData.at("Invincibility"));
	myDamage = zombieData.at("Damage");
	mySpeed = zombieData.at("MovementSpeed");
	myMaxSpeed = zombieData.at("MaxSpeedCap");
	myDetectionRange = zombieData.at("DetectionRange");
	myKnockback = zombieData.at("KnockBack");

	myPhysicsController.Init(GetScene(), mySprite->GetSize());
	myPhysicsController.SetGravity({ 0.0f, 1000.0f }); // TODO: Read from JSON
}

void Enemy::SetTarget(std::shared_ptr<GameObject> aTarget)
{
	if (aTarget != nullptr)
	{
		myTarget = aTarget;
	}
}
