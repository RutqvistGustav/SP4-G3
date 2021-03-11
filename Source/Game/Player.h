#pragma once

#include "GameObject.h"

#include <memory>
#include <json.hpp>

class PlayerWeaponController;
class SpriteWrapper;

namespace CommonUtilities
{
    class Input;
}

class InputInterface;

class Player :
    public GameObject
{
public:
    
    Player(Scene* aScene);
    virtual ~Player() override;

    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void ApplyForce(const CU::Vector2<float>& aForce);

    void Controller(const float aDeltaTime, InputInterface* anInput);

private:

    std::unique_ptr<PlayerWeaponController> myWeaponController;

    std::shared_ptr<SpriteWrapper> mySprite;

    // Movement
    bool myIsMovingLeft = false;
    bool myIsMovingRight = false;

    float mySpeed;
    float myMaxSpeed;
    float myStopAtVelocity; 
    float myGravity;
    double myReduceMovementSpeed;

    // Jump
    bool myIsJumping = false;
    bool myHasRemovedNegativeVel = false;
    int myJumpCharges;
    int myJumpChargeReset;
    float myJumpStrength;
    float myJumpDuration;
    float myJumpDurationReset;

    bool myGravityActive = false;

    CU::Vector2<float> myVel;

    // Movement
    CU::Vector2<float> GetDirection(InputInterface* anInput);
    void PlayerInput(InputInterface* anInput);

    void Movement(const float aDeltaTime, InputInterface* anInput);
    void BrakeMovement(const float aDeltaTime);
    void Jump(const float aDeltaTime);

    // Constructor
    void InitVariables(nlohmann::json someData);

    // Tools
    void ImGui();
};

