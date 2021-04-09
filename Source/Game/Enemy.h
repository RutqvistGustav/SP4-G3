#pragma once

#include "GameObject.h"
#include "PowerUpType.h"
#include "EntityPhysicsController.h"
#include "CharacterAnimator.h"

#include "EnemyType.h"

#include <memory>

class Health;

class Enemy :
    public GameObject
{
public:
    Enemy(Scene* aScene, EnemyType aEnemyType);
    virtual ~Enemy();

    virtual void Init() override;

    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;
    
    virtual void ApplyForce(const CU::Vector2<float>& aForce);
    virtual const int DealDamage();
    virtual void TakeDamage(const int aDamage);
    virtual void InitEnemyJsonValues(const std::string& aJsonPath);
    virtual PowerUpType GetLootType();
    virtual void SetLootType(const PowerUpType aLootType);

    void SetTarget(std::shared_ptr<GameObject> aTarget);

    virtual void SetPosition(const CU::Vector2<float> aPosition) override;

    void SetInitialPosition(const CU::Vector2<float>& anInitialPosition);
    const CU::Vector2<float>& GetInitialPosition() const;

    inline EnemyType GetType() const { return myType; }

protected:

    virtual void OnEnter(const CollisionInfo& someCollisionInfo) override;
    virtual void OnStay(const CollisionInfo& someCollisionInfo) override;
    virtual void OnExit(const CollisionInfo& someCollisionInfo) override;

protected:

    int myDamage;
    float mySpeed;
    float myMaxSpeed;
    float myDetectionRange;
    float myKnockback;
    float myGravity;
    PowerUpType myLoot;

    CU::Vector2<float> myColliderSize;
    CU::Vector2<float> mySpriteShift;

    std::shared_ptr<GameObject> myTarget;
    std::unique_ptr<Health> myHealth;

    CharacterAnimator myCharacterAnimator;

    float myKnockbackTimer{};

    bool myIsPlayerInRange{};

    EnemyType myType;

    CU::Vector2<float> myInitialPosition;

    EntityPhysicsController myPhysicsController;
};

