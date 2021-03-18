#pragma once
#include "GameObject.h"
#include "JsonData.h"

class GrappleHookProjectile :
    public GameObject
{
public:
    GrappleHookProjectile(Scene* aScene);
    ~GrappleHookProjectile() = default;

    void Init(const JsonData& someJsonData);
    void SetVariables(float aMaxDistance, float aHookSpeed, float aContractSpeed); // temp
    void Update(const float aDeltaTime, const CU::Vector2<float>& aPlayerPosition);
    void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;
    void OnCollision(GameObject* /*GrapplingHook point*/) override;

    void Movement(const float aDeltaTime, const CU::Vector2<float>& aPlayerPosition);
    bool HasFoundGrapplingTarget();
    void SpawnProjectile(const CU::Vector2<float> aDirection);
    void ResetProjectile();
    CU::Vector2<float>& GetGrapplingPoint();

private:
    bool myIsFiring = false;
    bool myHasFoundValidTarget = false;

    float myMaxDistance{};
    float myHookSpeed{};
    float myContractSpeed{};

    CU::Vector2<float> myDistanceTraveled;
    CU::Vector2<float> myGrapplingPoint;
    CU::Vector2<float> myDirection;
};

