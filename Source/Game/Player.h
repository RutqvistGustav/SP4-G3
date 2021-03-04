#pragma once
#include "GameObject.h"

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

    void Controller(const float aDeltaTime, CommonUtilities::Input* anInput);
    void Shoot();
    void Grapple();

private:
    float mySpeed;
    // Weapon myShotgun;

    CU::Vector2<float> GetVel_KeyboardInput(CommonUtilities::Input* anInput);
    void MouseInput(CommonUtilities::Input* anInput);
};

