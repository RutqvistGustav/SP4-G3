#pragma once
#include "GameObject.h"
#include <memory>
#include "CollisionListener.h"
#include <any>

class HealthBar;
class AmmoCounter;
class UIHook;

class HUD :
    public GameObject,
    public CollisionListener
{
public:
    HUD(Scene* aScene);
    ~HUD() = default;

    virtual void Init() override;
    virtual void Update(CU::Vector2<float> aPlayerPosition);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void OnCollision(std::any) override;

    HealthBar* GetHealthBar();
    AmmoCounter* GetAmmoCounter();
    UIHook* GetHookIcon();

private:
    std::unique_ptr<HealthBar> myHealthBar;
    std::unique_ptr<AmmoCounter> myAmmoCounter;
    std::unique_ptr<UIHook> myHookIcon;
};

