#pragma once
#include <memory>

#include "MenuScene.h"

class SpriteWrapper;

class PauseMenu :
    public MenuScene
{
public:
    PauseMenu();
    virtual ~PauseMenu() override;

    virtual void Init() override;
    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

    const bool IsGamePaused();

private:
    void InitButtons() ;
    void MouseClicked(GameObject* aTarget);

private:
    bool myPauseIsActive = true;
    std::shared_ptr<SpriteWrapper> myBackGround;
};

