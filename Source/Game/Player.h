#pragma once
#include "GameObject.h"
#include <memory>

class SpriteWrapper;

namespace CommonUtilities
{
    class Input;
}

class Player :
    public GameObject
{
public:
    Player();
    virtual ~Player() override;

    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void Controller(const float aDeltaTime, CU::Input* anInput);
    void Shoot();
    void Grapple();

    
private:
    std::shared_ptr<SpriteWrapper> mySprite;

    bool myIsMoving = false;

    float mySpeed;
    float myMaxSpeed = 2000.0f;
    float myReduceMovementSpeed = 0.001f;
    float myStopAtVelocity = 100.0f;
    float myGravity = 50.0f;
    CU::Vector2<float> myVel;

    CU::Vector2<float> GetVel_KeyboardInput(CU::Input* anInput);
    void MouseInput(CU::Input* anInput);

    // Movement
    void Movement(const float aDeltaTime, CU::Input* anInput);
    void BrakeMovement(const float aDeltaTime);
    void Jump();
};

