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
        Empty = 0
    };

    AmmoCounter(Scene* aScene);
    AmmoCounter() = default;

    virtual void Init() override;
    virtual void Update(CU::Vector2<float> aPlayerPosition);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void RemoveBullet();
    void Reload();

private:
    void UpdatePosition(CU::Vector2<float> aPlayerPosition);
    void InitSprites(nlohmann::json someData);

    CU::Vector2<float> myDistanceFromPlayer;

    unsigned int myCurrentBullets;
    unsigned int myResetBullets;

    std::shared_ptr<SpriteWrapper> mySecondSprite;
    CU::Vector2<float> mySpriteDistance{};
};

