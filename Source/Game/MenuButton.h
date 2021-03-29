#pragma once
#include "GameObject.h"

class Collider;

class MenuButton :
    public GameObject
{
public:
    MenuButton(Scene* aScene, const char* aSpritePath, const char* aSpritePath2, GameObjectTag aTag);
    virtual ~MenuButton() override;


    virtual void Init() override;
    virtual void Update();
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext & aRenderContext) override;
    void SetPosition(const CU::Vector2<float> aPosition);

private:
    virtual void OnCollision(GameObject* aGameObject);

    std::shared_ptr<SpriteWrapper> myHoverSprite;
    bool myHover;
};

