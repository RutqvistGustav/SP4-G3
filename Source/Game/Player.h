#pragma once

#include "GameObject.h"
#include "CharacterAnimator.h"

#include "CheckpointMessage.h"

#include "CollisionListener.h"

#include "CheckpointObjectData.h"

// TODO: Refactor so player does not use json library directly
#include <nlohmann/json.hpp>

#include <memory>
#include "PowerUpType.h"

#include "EntityPhysicsController.h"

class PlayerWeaponController;
class SpriteWrapper;
class SpriteSheetAnimation;
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

    void StopMovement();

    void SetControllerActive(const bool aState);
    void ActivatePowerUp(PowerUpType aPowerUpType);
    void DisablePowerUp();
    virtual void SetPosition(const CU::Vector2<float> aPosition) override;

    //Health Management
    void TakeDamage(const int aDamage);
    void AddHealth(const int aHealthAmount);
    
    CharacterAnimator* GetCharacterAnimator() { return &myCharacterAnimator; }

protected:

    struct PlayerCheckpointData : public CheckpointObjectData
    {
        CU::Vector2<float> myPosition;
    };

    virtual GameMessageAction OnMessage(const GameMessage aMessage, const CheckpointMessageData* someMessageData) override;

private:

    // Movement
    void Move(const float aDeltaTime, InputInterface* anInput);

    // Tools
    CU::Vector2<float> GetDirection(InputInterface* anInput);

    void InitVariables(nlohmann::json someData);
    void ImGui();

private:

    EntityPhysicsController myPhysicsController;
    CU::Vector2<float> myMovementVelocity;

    Camera* myCamera;
    float myCameraFollowSpeed;

    std::unique_ptr<PlayerWeaponController> myWeaponController;
    std::unique_ptr<HUD> myHUD;

    CharacterAnimator myCharacterAnimator;

    // JSON
    CU::Vector2<float> mySpriteShift;
    float myColliderWidth{};
    float myColliderHeight{};

    // Movement
    bool myIsControllerActive = true;
    bool myIsMovingLeft = false;
    bool myIsMovingRight = false;
    bool myIsOnGround = false;

    float mySpeed;
    float myMaxSpeed;
    float myStopAtVelocity;
    float myReduceMovementSpeed;

    float myBerserkSpeed{};
    float myGravity{};

    // Jump
    int myJumpCharges;
    int myJumpChargeReset;

    float myJumpStrength;
    float myCoyoteTime{};
    float myCoyoteTimeReset{};

    std::unique_ptr<Health> myHealth;
};
