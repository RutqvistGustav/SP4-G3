#pragma once
#include "GameObject.h"
#include "JsonData.h"
#include "WeaponHolder.h"

class IWeaponHolder;

class GrappleHookProjectile :
    public GameObject
{
public:
    GrappleHookProjectile(Scene* aScene, IWeaponHolder* aWeaponHolder);
    ~GrappleHookProjectile() = default;

    void Init(const JsonData& someJsonData);
    void SetVariables(float aMaxDistance, float aHookSpeed, float aContractSpeed); // temp
    void Update(const float aDeltaTime, const CU::Vector2<float>& aPlayerPosition);
    void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;
    void OnCollision(GameObject* /*GrapplingHook point*/) override;

    void Movement(const float aDeltaTime, const CU::Vector2<float>& aPlayerPosition);
    void SpawnProjectile(const CU::Vector2<float> aDirection);
    void ResetProjectile();

    bool HasFoundGrapplingTarget();
    CU::Vector2<float>& GetGrapplingPoint();

private:
    bool myIsFiring = false;
    bool myHasFoundValidTarget = false;
    bool myHasSentPosition = false;

    float myDistanceTraveled{};

    float myMaxDistance{};
    float myHookSpeed{};
    float myContractSpeed{};


    CU::Vector2<float> myGrapplingPoint;
    CU::Vector2<float> myDirection;

    IWeaponHolder* myWeaponHolder;
};

