#include "stdafx.h"
#include "Enemy.h"
#include "Scene.h"
#include "Health.h"
#include "GlobalServiceProvider.h"
#include "AudioManager.h"
#include "JsonManager.h"
#include "SpriteSheetAnimation.h"
#include "CharacterAnimator.h"

#include "Player.h"

#include "CollisionInfo.h"

#include "SpriteWrapper.h"

#include "GameMessenger.h"
#include "SpawnParticleEffectMessage.h"

Enemy::Enemy(Scene* aScene, EnemyType aEnemyType)
	: GameObject(aScene, GameObjectTag::Enemy),
	myType(aEnemyType),
	myCharacterAnimator(aScene, "Animations/Zombie.json")
{}

Enemy::~Enemy() = default;

void Enemy::Init()
{
	GameObject::Init();

	myCollider->SetLayer(CollisionLayer::Entity);
	myCollider->SetBoxSize(myColliderSize);

	myPhysicsController.Init(GetScene(), myCollider->GetBoxSize());
	myPhysicsController.SetPosition(GetPosition());
	myPhysicsController.SetGravity({ 0.0f, myGravity });

	mySprite->SetLayer(GameLayer::Enemy);
}

void Enemy::Update(const float aDeltaTime, UpdateContext& /*anUpdateContext*/)
{
	if (!myHealth->IsDead())
	{
		if (myKnockbackTimer > 0.0f)
		{
			myKnockbackTimer -= aDeltaTime;
		}

		myPhysicsController.Update(aDeltaTime);
		SetPosition(myPhysicsController.GetPosition());

		if (myPhysicsController.GetVelocity().x > 0.0f)
		{
			myCharacterAnimator.SetDirection(1.0f);
		}
		else if (myPhysicsController.GetVelocity().x < 0.0f)
		{
			myCharacterAnimator.SetDirection(-1.0f);
		}

		myHealth->Update(aDeltaTime);
	}

	if (myHealth->IsDead() && myCharacterAnimator.HasEnded())
	{
		SetDeleteThisFrame();
	}

	myCharacterAnimator.Update(aDeltaTime);
	myCharacterAnimator.ApplyToSprite(mySprite);
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

	if (myHealth->IsDead())
	{
		myCharacterAnimator.SetState(CharacterAnimator::State::Death);
		GetScene()->GetGlobalServiceProvider()->GetAudioManager()->PlaySfx("Sound/Enemy/Zombie_Groan_02.mp3");

	}

	//SpawnParticleEffectMessageData spawnData{};
	//spawnData.myType = ParticleEffectType::BloodSplatter;
	//spawnData.myPosition = GetPosition();

	//GetScene()->GetGlobalServiceProvider()->GetGameMessenger()->Send(GameMessage::SpawnParticleEffect, &spawnData);
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
	myRoamMaxSpeed = zombieData.at("MaxRoamSpeedCap");
	myDetectionRange = zombieData.at("DetectionRange");
	myKnockback = zombieData.at("KnockBack");
	myGravity = zombieData.at("Gravity");


	myColliderSize = mySprite->GetSize();

	myColliderSize.x = zombieData.value("ColliderWidth", myColliderSize.x);
	myColliderSize.y = zombieData.value("ColliderHeight", myColliderSize.y);

	mySpriteShift.x = zombieData.value("SpriteShiftX", mySpriteShift.x);
	mySpriteShift.y = zombieData.value("SpriteShiftY", mySpriteShift.y);
}

PowerUpType Enemy::GetLootType()
{
	return myLoot;
}

void Enemy::SetLootType(const PowerUpType aLootType)
{
	myLoot = aLootType;
}

void Enemy::SetShouldRoam(const bool aShouldRoam)
{
	myShouldRoam = aShouldRoam;
}

bool Enemy::GetShouldRoam() const
{
	return myShouldRoam;
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

	mySprite->SetPosition(aPosition + CU::Vector2<float>(mySpriteShift.x * myCharacterAnimator.GetDirection(), mySpriteShift.y));
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

void Enemy::OnEnter(const CollisionInfo& someCollisionInfo)
{
	GameObject* gameObject = someCollisionInfo.myOtherCollider->GetGameObject();

	if (gameObject != nullptr && gameObject->GetTag() == GameObjectTag::Player)
	{
		myIsPlayerInRange = true;
	}
}

void Enemy::OnStay(const CollisionInfo& someCollisionInfo)
{
	GameObject* gameObject = someCollisionInfo.myOtherCollider->GetGameObject();

	if (gameObject != nullptr && gameObject->GetTag() == GameObjectTag::Player && !myHealth->IsDead())
	{
		Player* player = static_cast<Player*>(gameObject);

		player->TakeDamage(myDamage);

		myCharacterAnimator.SetState(CharacterAnimator::State::Attack);

		if (myKnockbackTimer <= 0.0f)
		{
			CU::Vector2<float> direction = player->GetPosition() - GetPosition();
			player->ApplyForce(direction.GetNormalized() * myKnockback);

			myKnockbackTimer = 0.1f;
		}
	}
	else
	{
		myCharacterAnimator.SetState(CharacterAnimator::State::Idle);
	}
}

void Enemy::OnExit(const CollisionInfo& someCollisionInfo)
{
	GameObject* gameObject = someCollisionInfo.myOtherCollider->GetGameObject();

	if (gameObject != nullptr && gameObject->GetTag() == GameObjectTag::Player)
	{
		myIsPlayerInRange = false;
	}
}
