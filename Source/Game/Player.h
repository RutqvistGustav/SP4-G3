#pragma once
#include "GameObject.h"

#include "CheckpointMessage.h"

// TODO: Refactor so player does not use json library directly
#include <nlohmann/json.hpp>

#include <memory>

#include "EntityPhysicsController.h"

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

    void StopMovement();

    //Health Management
    void TakeDamage(const int aDamage);
    void AddHealth(const int aHealthAmount);
protected:

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

    Camera* myCamera;
    float myCameraFollowSpeed;

    std::unique_ptr<PlayerWeaponController> myWeaponController;
    std::unique_ptr<HUD> myHUD;

    // Movement
    float mySpeed;
    float myMaxSpeed;
    float myStopAtVelocity;
    float myReduceMovementSpeed;

    float myGravity;

    // Jump
    int myJumpCharges;
    int myJumpChargeReset;

    float myJumpStrength;

    std::unique_ptr<Health> myHealth;
};
