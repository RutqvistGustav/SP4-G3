#pragma once
#include "Scene.h"

class MenuButton;
class SpriteWrapper;

class TiledParser;
class TiledRenderer;
class TiledCollision;

class PauseMenu :
    public Scene
{
public:
    PauseMenu();
    virtual ~PauseMenu() override;

    virtual void Init() override;
    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:
    void InitButtons();

    std::unique_ptr<MenuButton> myStartButton;
    std::unique_ptr<MenuButton> myQuitButton;

    std::vector<std::unique_ptr<MenuButton>> myButtons;

    std::shared_ptr<SpriteWrapper> myBackGround;

    std::unique_ptr<TiledParser> myTiledParser;
    std::unique_ptr<TiledRenderer> myTiledRenderer;
    std::unique_ptr<TiledCollision> myTiledCollision;
};

