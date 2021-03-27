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
    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext);
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;
    void SetPosition(const CU::Vector2<float> aPosition);
    void SetColliderSize(const CU::Vector2<float> aSize);

private:
    virtual void OnCollision(GameObject* aGameObject);

    std::shared_ptr<SpriteWrapper> myBody;
};

