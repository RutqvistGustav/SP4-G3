#pragma once
#include "Scene.h"
class MainMenu :
    public Scene
{
public:
	MainMenu();
	virtual ~MainMenu() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:


};

