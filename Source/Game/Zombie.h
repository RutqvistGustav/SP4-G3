#pragma once
#include "Enemy.h"
#include "TileType.h"

class Zombie :
    public Enemy
{
public:
    Zombie(Scene* aScene);
    ~Zombie();

    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void         Movement(const float aDeltaTime);
    void         IdleMovement(const float aDeltaTime);
    void         UpdateGravity(const float aDeltaTime);
    void         OnCollision(GameObject* aGameObject) override;
    void         OnCollision(TileType aTileType, CU::Vector2<float> anOffset) override;
    bool         CheckIdle();
    void         ApplyForce(const CU::Vector2<float>& aForce) override;
private:
    float myGravity = 0.0f;
    CU::Vector2<float> myVelocity;
};

