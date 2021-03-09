#pragma once
#include "GameObject.h"
#include <memory>
#include <json.hpp>

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

    // Movement
    bool myIsMovingLeft = false;
    bool myIsMovingRight = false;

    float mySpeed;
    float myMaxSpeed;
    float myReduceMovementSpeed;
    float myStopAtVelocity;
    float myGravity;

    // Jump
    bool myIsJumping = false;
    bool myHasRemovedNegativeVel = false;
    unsigned int myJumpCharges;
    unsigned int myJumpChargeReset;
    float myJumpStrength;
    float myJumpDuration;
    float myJumpDurationReset;

    bool myGravityActive = false;

    CU::Vector2<float> myVel;

    CU::Vector2<float> GetVel_KeyboardInput(CU::Input* anInput);
    void MouseInput(CU::Input* anInput);

    // Movement
    void Movement(const float aDeltaTime, CU::Input* anInput);
    void BrakeMovement(const float aDeltaTime);
    void Jump(const float aDeltaTime);

    // Constructor
    void InitVariables(nlohmann::json someData);
};

