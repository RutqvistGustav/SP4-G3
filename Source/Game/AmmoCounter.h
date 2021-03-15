#pragma once
#include "GameObject.h"
#include <memory>
#include "nlohmann/json.hpp"

class SpriteWrapper;

class AmmoCounter :
    public GameObject
{
public:
    enum AmmoState
    {
        Loaded = 2,
        HalfEmpty = 1,
        Reloading = 0
    };

    AmmoCounter(Scene* aScene);
    AmmoCounter() = default;

    virtual void Update(CU::Vector2<float> aPlayerPosition);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void RemoveBullet();
    void Reload();

private:
    void UpdatePosition(CU::Vector2<float> aPlayerPosition);
    void InitSprites(nlohmann::json someData);

    AmmoState myState;
    CU::Vector2<float> myDistanceFromPlayer;

    bool myPowerUpActive = false;

    unsigned int myCurrentBullets;
    unsigned int myResetBullets;

    // GameObject holds fully loaded state.
    std::shared_ptr<SpriteWrapper> myHalfState;
    std::shared_ptr<SpriteWrapper> myEmptyState;
    // Reload animation
};

