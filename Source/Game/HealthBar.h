#pragma once
#include "GameObject.h"
#include "PowerUpType.h"

class HealthBar :
    public GameObject
{
public:
    HealthBar(Scene* aScene);
    ~HealthBar() = default;

    virtual void Init() override;
    virtual void Update(CU::Vector2<float> aPlayerPosition);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void OnCollision(GameObject*) override;

    void RemoveHP();
    void AddHP();
    void ActivatePowerUp(PowerUpType aPowerUpType);

private:
    void UpdatePosition(CU::Vector2<float> aPlayerPosition);
    CU::Vector2<float> myDistanceFromPlayer;

    PowerUpType myPowerUpType;
    float myBerserkDuration{};
    float myBerserkDurationReset{};
    float mySniperShotDuration{};
    float mySniperShotDurationReset{};

    std::shared_ptr<SpriteWrapper> myHealthBarFill;
    std::shared_ptr<SpriteWrapper> myPowerUpFrame;
    std::shared_ptr<SpriteWrapper> myPowerUpFill;
};

