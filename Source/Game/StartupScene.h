#pragma once
#include "Scene.h"

class CutscenePlayer;

class StartupScene :
    public Scene
{
public:
    StartupScene();
    virtual ~StartupScene() override;

    virtual void Init() override;

    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:
    std::unique_ptr<CutscenePlayer> myIntro;

};

