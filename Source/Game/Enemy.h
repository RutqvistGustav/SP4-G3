#pragma once
#include "GameObject.h"


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
    //virtual void DealDamage();
    //virtual void TakeDamage();
    //virtual void Behavior();

    void SetTarget(std::shared_ptr<GameObject> aTarget);

protected:
    int myHealth;
    int myDamage;
    float mySpeed;
    float myMaxSpeed;
    float myDetectionRange;
    std::shared_ptr<GameObject> myTarget;
};

