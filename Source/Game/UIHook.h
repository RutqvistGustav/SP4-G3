#pragma once
#include "GameObject.h"
#include <memory>

class SpriteWrapper;

class UIHook :
    public GameObject
{
public:
    UIHook(Scene* aScene);
    ~UIHook() = default;

    virtual void Update(CU::Vector2<float> aPlayerPosition);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void SetHighlight(const bool aIsActive);

private:
    void UpdatePosition(CU::Vector2<float> aPlayerPosition);

    CU::Vector2<float> myDistanceFromPlayer;
    bool myIsHighlightActive = false;

    std::shared_ptr<SpriteWrapper> mySpriteHighlighed;
};

