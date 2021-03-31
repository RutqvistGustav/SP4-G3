#pragma once
#include "GameObject.h"
#include <memory>

class HealthBar;
class AmmoCounter;

class HUD :
    public GameObject
{
public:
    HUD(Scene* aScene);
    ~HUD() = default;

    virtual void Init() override;
    virtual void Update(CU::Vector2<float> aPlayerPosition);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void OnCollision(GameObject*) override;

    HealthBar* GetHealthBar();
    AmmoCounter* GetAmmoCounter();

private:
    std::unique_ptr<HealthBar> myHealthBar;
    std::unique_ptr<AmmoCounter> myAmmoCounter;
};

