#pragma once
#include "GameObject.h"


class Enemy :
    public GameObject
{
public:
    Enemy(Scene* aScene, const char* aSpritePath = nullptr);
    virtual ~Enemy();

    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext/*, CU::Vector2& aPlayer*/) override;  // Need Player position for tracking
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;
    
    //virtual void OnCollision();
    //virtual void DealDamage();
    //virtual void TakeDamage();
    //virtual void Behavior();

protected:
    int myHealth;
    int myDamage;
    float mySpeed;
    float myMaxSpeed;
};

