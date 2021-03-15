#pragma once
#include "GameObject.h"
#include <memory>

class HealthBar;
class AmmoCounter;
class UIHook;

class HUD :
    public GameObject
{
public:
    HUD(Scene* aScene);
    ~HUD() = default;

    virtual void Update(CU::Vector2<float> aPlayerPosition);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    HealthBar* GetHealthBar();
    AmmoCounter* GetAmmoCounter();
    UIHook* GetHookIcon();

private:
    std::unique_ptr<HealthBar> myHealthBar;
    std::unique_ptr<AmmoCounter> myAmmoCounter;
    std::unique_ptr<UIHook> myHookIcon;
};

