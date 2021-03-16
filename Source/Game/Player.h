#pragma once

#include "GameObject.h"

#include "CheckpointMessage.h"

// TODO: Refactor so player does not use json library directly
#include <nlohmann/json.hpp>

#include <memory>

class PlayerWeaponController;
class SpriteWrapper;
class HUD;

namespace CommonUtilities
{
    class Input;
}

class Camera;
class InputInterface;

class Player :
    public GameObject,
    public CheckpointMessage
{
public:
    
    Player(Scene* aScene);
    virtual ~Player() override;

    virtual void Init() override;
    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void ApplyForce(const CU::Vector2<float>& aForce);

    void Controller(const float aDeltaTime, InputInterface* anInput);

    void OnCollision(GameObject*) override;

    void StopMovement();

protected:

    virtual GameMessageAction OnMessage(const GameMessage aMessage, const CheckpointMessageData* someMessageData) override;

private:
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

private:

    Camera* myCamera;
    float myCameraFollowSpeed;

    std::unique_ptr<PlayerWeaponController> myWeaponController;
    std::unique_ptr<HUD> myHUD;

    // Movement
    bool myIsMovingLeft = false;
    bool myIsMovingRight = false;

    float mySpeed;
    bool myOnGround;
    // Weapon myShotgun;
    float myMaxSpeed;
    float myStopAtVelocity;

    float myGravity;

    double myReduceMovementSpeed;

    CU::Vector2<float> myVel;

    // Jump
    bool myIsJumping = false;
    bool myHasRemovedNegativeVel = false;
    bool myGravityActive = false;

    int myJumpCharges;
    int myJumpChargeReset;

    float myJumpStrength;
    float myJumpDuration;
    float myJumpDurationReset;

};

//TODO:check if the collider is solid