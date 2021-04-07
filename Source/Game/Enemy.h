#pragma once

#include "GameObject.h"
#include "PowerUpType.h"
#include "EntityPhysicsController.h"

#include <memory>

class Health;

class Enemy :
    public GameObject
{
public:
    Enemy(Scene* aScene, const char* aSpritePath = nullptr);
    virtual ~Enemy();

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

protected:


    virtual void OnStay(const CollisionInfo& someCollisionInfo) override;

protected:

    int myDamage;
    float mySpeed;
    float myMaxSpeed;
    float myDetectionRange;
    float myKnockback;
    PowerUpType myLoot;
    std::shared_ptr<GameObject> myTarget;
    std::unique_ptr<Health> myHealth;
    CU::Vector2<float> myPreviousVelocity{};

    float myKnockbackTimer{};

    EntityPhysicsController myPhysicsController;
};

