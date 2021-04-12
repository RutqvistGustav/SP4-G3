#pragma once
#include "Scene.h"

class CutscenePlayer;

class OutroScene :
    public Scene
{
public:
    OutroScene();
    virtual ~OutroScene() override;

    virtual void Init() override;

    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
    virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:
    void SkipCutscene(UpdateContext& anUpdateContext);

private:
    std::unique_ptr<CutscenePlayer> myOutro;
};

