#pragma once
#include "Enemy.h"
class JetPack :
    public Enemy
{
public:
    JetPack(Scene* aScene);
    ~JetPack();

    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    void OnCollision(GameObject* aGameObject) override;

private:

};

