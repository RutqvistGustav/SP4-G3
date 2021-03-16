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

    void OnCollision(GameObject*) override;

    void RemoveHP();
    void AddHP();

private:
    CU::Vector2<float> myDistanceFromPlayer;

    void UpdatePosition(CU::Vector2<float> aPlayerPosition);
};

