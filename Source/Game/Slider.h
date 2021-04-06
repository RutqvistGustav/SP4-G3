#pragma once

#include "GameObject.h"

#include <functional>

class Collider;

class Slider :
    public GameObject
{
public:

    using ValueChangeCallback = std::function<void(float aCurrentValue)>;

    Slider(Scene* aScene, const char* aSpritePath, GameObjectTag aTag);
    virtual ~Slider() override;

    virtual void Init() override;

    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void SetPosition(const CU::Vector2<float> aPosition, bool aSetBodyPos);

    void SetValueChangeCallback(const ValueChangeCallback& aValueChangeCallback);

    void SetSlidePercentage(float aPercentage);
    float GetSlidePercentage() const;

private:

    void MoveWithMouse();

    float ComputeSlidePercentage(const float aPositionX) const;

    virtual void OnStay(const CollisionInfo& someCollisionInfo);
    virtual void OnExit(const CollisionInfo& someCollisionInfo);

private:

    float myLeftBoundry;
    float myRightBoundry;

    std::shared_ptr<SpriteWrapper> myBody;

    ValueChangeCallback myValueChangeCallback{};

    bool myIsTrackingMouse{};
    bool myIsMouseOnSlider{};
    MousePointer* myMousePointer{};

};
