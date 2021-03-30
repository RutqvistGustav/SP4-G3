#pragma once
#include "GameObject.h"

#include "CheckpointMessage.h"

// TODO: Refactor so player does not use json library directly
#include <nlohmann/json.hpp>

#include <memory>
#include "PowerUpType.h"

class PlayerWeaponController;
class SpriteWrapper;
class HUD;
class Health;

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

    void OnCollision(GameObject*) override;
    void OnCollision(TileType aTileType, CU::Vector2<float> anOffset) override;

    void StopMovement();

    void SetControllerActive(const bool aState);
    void ActivatePowerUp(PowerUpType aPowerUpType);
    void DisablePowerUp();

    //Health Management
    void TakeDamage(const int aDamage);
    void AddHealth(const int aHealthAmount);
protected:

    virtual GameMessageAction OnMessage(const GameMessage aMessage, const CheckpointMessageData* someMessageData) override;

private:
    // Movement
    void Movement(const float aDeltaTime, InputInterface* anInput);
    void BrakeMovement(const float aDeltaTime);
    void Jump(const float aDeltaTime);

    // Tools
    CU::Vector2<float> GetDirection(InputInterface* anInput);
    void InitVariables(nlohmann::json someData);
    void PlayerInput(InputInterface* anInput);
    void ImGui();



private:
    Camera* myCamera;
    float myCameraFollowSpeed;

    std::unique_ptr<PlayerWeaponController> myWeaponController;
    std::unique_ptr<HUD> myHUD;

    // Movement
    bool myIsControllerActive = true;
    bool myIsMovingLeft = false;
    bool myIsMovingRight = false;
    bool myIsOnGround = false;

    float mySpeed{};
    float myMaxSpeed{};
    float myStopAtVelocity{};
    double myReduceMovementSpeed{};
    CU::Vector2<float> myVel;

    float myBerserkSpeed{};
    float myGravity{};

    // Jump
    bool myIsJumping = false;
    bool myHasRemovedNegativeVel = false;
    bool myGravityActive = true;

    int myJumpCharges{};
    int myJumpChargeReset{};

    float myJumpStrength{};
    float myJumpDuration{};
    float myJumpDurationReset{};

    std::unique_ptr<Health> myHealth;
};
