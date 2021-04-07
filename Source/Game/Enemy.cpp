#include "stdafx.h"
#include "Enemy.h"
#include "Scene.h"
#include "Health.h"
#include "GlobalServiceProvider.h"
#include "JsonManager.h"

#include "Player.h"

#include "CollisionInfo.h"

#include "SpriteWrapper.h"

#include <nlohmann/json.hpp>


Enemy::Enemy(Scene* aScene, EnemyType aEnemyType, const char* aSpritePath)
	: GameObject(aScene, GameObjectTag::Enemy, aSpritePath),
	myType(aEnemyType)
{}

Enemy::~Enemy() = default;

void Enemy::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	if (myKnockbackTimer > 0.0f)
	{
		myKnockbackTimer -= aDeltaTime;
	}

	myPhysicsController.Update(aDeltaTime);
	GameObject::SetPosition(myPhysicsController.GetPosition());
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
	nlohmann::json zombieData = data.at(aJsonPath);
	myHealth = std::make_unique<Health>(zombieData.at("Health"));
	myHealth->SetInvincibilityTimer(zombieData.at("Invincibility"));
	myDamage = zombieData.at("Damage");
	mySpeed = zombieData.at("MovementSpeed");
	myMaxSpeed = zombieData.at("MaxSpeedCap");
	myDetectionRange = zombieData.at("DetectionRange");
	myKnockback = zombieData.at("KnockBack");

	myPhysicsController.Init(GetScene(), mySprite->GetSize());
	myPhysicsController.SetGravity({ 0.0f, zombieData.at("Gravity") });
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

void Enemy::SetPosition(const CU::Vector2<float> aPosition)
{
	GameObject::SetPosition(aPosition);
	myPhysicsController.SetPosition(aPosition);
}

void Enemy::SetInitialPosition(const CU::Vector2<float>& anInitialPosition)
{
	myInitialPosition = anInitialPosition;
}

const CU::Vector2<float>& Enemy::GetInitialPosition() const
{
	return myInitialPosition;
}

void Enemy::OnStay(const CollisionInfo& someCollisionInfo)
{
	GameObject* gameObject = someCollisionInfo.myOtherCollider->GetGameObject();

	if (gameObject != nullptr && gameObject->GetTag() == GameObjectTag::Player)
	{
		Player* player = static_cast<Player*>(gameObject);

		player->TakeDamage(myDamage);

		if (myKnockbackTimer <= 0.0f)
		{
			CU::Vector2<float> direction = player->GetPosition() - GetPosition();
			player->ApplyForce(direction.GetNormalized() * myKnockback);

			myKnockbackTimer = 0.1f;
		}
	}
}
