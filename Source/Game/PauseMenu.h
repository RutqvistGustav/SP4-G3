#pragma once
#include <memory>

#include "MenuScene.h"
#include "Settings.h"

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

    void Input(UpdateContext& anUpdateContext);
    const bool IsGamePaused();

private:
    void InitButtons() ;
    void MouseClicked(GameObject* aTarget);

private:
    bool myPauseIsActive = true;
    bool mySettingIsActive = false;

    std::unique_ptr<Settings> mySettings;
    std::shared_ptr<SpriteWrapper> myBackGround;
};

