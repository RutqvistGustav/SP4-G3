#pragma once
#include "GameObject.h"
class GrappleHookProjectile :
    public GameObject
{
public:
    GrappleHookProjectile(Scene* aScene);
    ~GrappleHookProjectile() = default;

    void Init() override;
    void Update(const float aDeltaTime, const CU::Vector2<float>& aPlayerPosition);
    void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;
    void OnCollision(GameObject* /*GrapplingHook point*/) override;

    void Movement(const float aDeltaTime);
    bool HasFoundGrapplingTarget();
    void SetIsFiring(const CU::Vector2<float> aPlayerPosition, const CU::Vector2<float> aDirection);
    void ResetProjectile();
    CU::Vector2<float>& GetGrapplingPoint();

private:
    bool myIsFiring = false;
    bool myHasFoundValidTarget = false;

    float myDistanceTraveled;
    float myMaxDistance{};
    float myHookSpeed{};
    float myContractSpeed{};

    CU::Vector2<float> myGrapplingPoint;
};

