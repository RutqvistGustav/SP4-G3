#pragma once
#include "Enemy.h"

class Zombie :
    public Enemy
{
public:
    Zombie(Scene* aScene);
    ~Zombie();

    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void         Movement(const float aDeltaTime);
    void         UpdateGravity(const float aDeltaTime);
    void         OnCollision(GameObject* aGameObject) override;

private:
    CU::Vector2<float> myVelocity;
    float myGravity = 0.0f;
};

