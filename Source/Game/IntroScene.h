#pragma once
#include "Scene.h"

class CutscenePlayer;

class IntroScene :
    public Scene
{
    public:
        IntroScene();
        virtual ~IntroScene() override;

        virtual void Init() override;

        virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
        virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:
    void SkipCutscene(UpdateContext& anUpdateContext);
    private:
        std::unique_ptr<CutscenePlayer> myIntro;
};

