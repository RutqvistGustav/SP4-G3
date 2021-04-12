#pragma once

#include "GameObject.h"
#include "PowerUpType.h"
#include "CollisionListener.h"

#include "SimpleEventObserver.h"

class Health;

class HealthBar :
    public GameObject,
    public SimpleEventObserver<int>
{
public:
    HealthBar(Scene* aScene, Health* aHealthInterface);
    ~HealthBar() = default;

    virtual void Init() override;

    virtual void Update(const float aDeltaTime, CU::Vector2<float> aPlayerPosition);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void ActivatePowerUp(PowerUpType aPowerUpType);
    void ReducePowerUpAmount(const float aDeltaTime);

private:

    void UpdatePosition(CU::Vector2<float> aPlayerPosition);

    virtual void OnEvent(int someNewHealth) override;

private:

    Health* myHealthInterface;

    CU::Vector2<float> myDistanceFromPlayer;

    PowerUpType myPowerUpType;

    bool myIsPowerUpActive = false;

    float myBerserkDuration{};
    float myBerserkDurationReset{};

    float myInitialHealthBarWidth;
    float myInitialPowerUpBarWidth;

    CU::Vector2<float> myHealthBarOffSet;
    CU::Vector2<float> myPowerupFrameOffSet;
    CU::Vector2<float> myPowerupBarOffSet;

    std::shared_ptr<SpriteWrapper> myHealthBar;
    std::shared_ptr<SpriteWrapper> myPowerUpFrame;
    std::shared_ptr<SpriteWrapper> myPowerUpBar;
};

