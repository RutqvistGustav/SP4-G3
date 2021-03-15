#pragma once
#include "GameObject.h"
#include <memory>
#include "json.hpp"

class SpriteWrapper;

class AmmoCounter :
    public GameObject
{
public:
    AmmoCounter(Scene* aScene);
    AmmoCounter() = default;

    virtual void Update(CU::Vector2<float> aPlayerPosition);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void RemoveShell();
    void Reload();

private:
    enum class AmmoState
    {
        Loaded,
        HalfEmpty,
        Empty,
        Reloading
    };
    void UpdatePosition(CU::Vector2<float> aPlayerPosition);
    void InitSprites(nlohmann::json someData);

    AmmoState myState;
    CU::Vector2<float> myDistanceFromPlayer;

    bool myPowerUpActive = false;

    unsigned int myBullets;
    unsigned int myResetBullets;

    // GameObject holds fully loaded state.
    std::shared_ptr<SpriteWrapper> myHalfState;
    std::shared_ptr<SpriteWrapper> myEmptyState;
    // Reload animation
};

