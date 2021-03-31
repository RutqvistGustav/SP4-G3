#pragma once
#include "GameObject.h"
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
    
    virtual void OnCollision(GameObject* aGameObject) = 0;
    virtual void OnCollision(TileType aTileType, CU::Vector2<float> anOffset) = 0;
    virtual void ApplyForce(const CU::Vector2<float>& aForce) = 0;
    virtual const int DealDamage();
    virtual void TakeDamage(const int aDamage);
    virtual void InitEnemyJsonValues(std::string& aJsonPath);

    void SetTarget(std::shared_ptr<GameObject> aTarget);

protected:
    int myDamage;
    float mySpeed;
    float myMaxSpeed;
    float myDetectionRange;
    float myKnockback;
    std::shared_ptr<GameObject> myTarget;
    std::unique_ptr<Health> myHealth;
};

