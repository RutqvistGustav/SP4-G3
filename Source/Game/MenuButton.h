#pragma once
#include "GameObject.h"
#include "CollisionListener.h"

class Collider;

class MenuButton :
    public GameObject,
    public CollisionListener
{
public:
    MenuButton(Scene* aScene, const char* aSpritePath, const char* aSpritePath2, GameObjectTag aTag);
    virtual ~MenuButton() override;

    virtual void Init() override;
    virtual void Update();
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext & aRenderContext) override;
    //void SetPosition(const CU::Vector2<float> aPosition);
    void SetColliderSize(const CU::Vector2<float> aSize);
    
    virtual void SetPosition(const CU::Vector2<float> aPosition) override;

private:

    virtual void OnEnter(const CollisionInfo& someCollisionInfo) override;
    virtual void OnExit(const CollisionInfo& someCollisionInfo) override;
    void SetPosition(const CU::Vector2<float> aPosition);

private:

    std::shared_ptr<SpriteWrapper> myHoverSprite;
    bool myHover;
};

