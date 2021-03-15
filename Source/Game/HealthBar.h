#pragma once
#include "GameObject.h"
class HealthBar :
    public GameObject
{
public:
    HealthBar(Scene* aScene);
    ~HealthBar() = default;

    virtual void Update(CU::Vector2<float> aPlayerPosition);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void RemoveHP();
    void AddHP();

private:
    CU::Vector2<float> myDistanceFromPlayer;
    /*
    Two sprites
    One for the frame
    the other for the red filling in the bar
    filling will decrease in size when taking damage
    */

    void UpdatePosition(CU::Vector2<float> aPlayerPosition);
};

