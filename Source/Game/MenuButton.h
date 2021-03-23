#pragma once
#include "GameObject.h"

class Collider;

class MenuButton :
    public GameObject
{
public:
    MenuButton(Scene* aScene, const char* aSpritePath);
    virtual ~MenuButton() override;


    virtual void Init() override;
    virtual void Update();
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext & aRenderContext) override;
    void SetPosition(const CU::Vector2<float> aPosition);

private:
};

