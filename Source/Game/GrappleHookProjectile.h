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
    void Update(const float aDeltaTime, const CU::Vector2<float>& aPlayerPosition);
    void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;
    void OnCollision(GameObject* /*GrapplingHook point*/) override;

    void SpawnProjectile(const CU::Vector2<float> aDirection);
    void ResetProjectile();

    CU::Vector2<float>& GetGrapplingPoint();

private:
    void Movement(const float aDeltaTime, const CU::Vector2<float>& aPlayerPosition);

    bool myIsFiring = false;
    bool myHasFoundTarget = false;

    float myDistanceTraveled{};
    float myMaxDistance{};
    float myHookSpeed{};
    float myContractSpeed{};
    float myCoolDown{};

    CU::Vector2<float> myGrapplingPoint;
    CU::Vector2<float> myDirection;

    IWeaponHolder* myWeaponHolder;
};

