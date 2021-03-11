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
    ~Player();

    void Update(const float aDeltaTime, CommonUtilities::Input* anInput);
    void Render();

    void Controller(const float aDeltaTime, CommonUtilities::Input* anInput);
    void Shoot();
    void Grapple();

    void OnCollision(const GameObject*) override;

private:
    float mySpeed;
    bool myOnGround;
    // Weapon myShotgun;

    CU::Vector2<float> GetVel_KeyboardInput(CommonUtilities::Input* anInput);
    void MouseInput(CommonUtilities::Input* anInput);
};

