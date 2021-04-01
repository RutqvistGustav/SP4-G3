#pragma once
#include "GameObject.h"
#include <memory>
#include "CollisionListener.h"
#include <any>

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

    HealthBar* GetHealthBar();
    AmmoCounter* GetAmmoCounter();

private:
    std::unique_ptr<HealthBar> myHealthBar;
    std::unique_ptr<AmmoCounter> myAmmoCounter;
};

