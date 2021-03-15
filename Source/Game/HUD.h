#pragma once
#include "GameObject.h"
#include <memory>

class HealthBar;

class HUD :
    public GameObject
{
public:
    HUD(Scene* aScene);
    ~HUD() = default;

    virtual void Update(CU::Vector2<float> aPlayerPosition);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    HealthBar* GetHealthBar();

private:
    std::unique_ptr<HealthBar> myHealthBar;
    // ammo counter
    // grappling hook icon
};

