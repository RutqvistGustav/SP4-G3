#pragma once
#include "GameObject.h"

class Collider;

class Slider :
    public GameObject
{
public:
    Slider(Scene* aScene, const char* aSpritePath, GameObjectTag aTag);
    virtual ~Slider() override;

    virtual void Init() override;
    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext, bool aLMBDown, CU::Vector2<float> aMousePos);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;
    void SetPosition(const CU::Vector2<float> aPosition, bool aSetBodyPos);
    void SetColliderSize(const CU::Vector2<float> aSize);

private:
    float myLeftBoundry;
    float myRightBoundry;

    bool myMove;

    std::shared_ptr<SpriteWrapper> myBody;

    void SetVolumePos();
    void CalculateVolume();
    virtual void OnCollision(GameObject* aGameObject);
    void PressedMove(float aPosX);
    void ClickedMove(CU::Vector2<float> aMousePos);
};

