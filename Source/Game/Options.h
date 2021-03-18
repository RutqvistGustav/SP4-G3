#pragma once
#include "Scene.h"

class MenuButton;

class Options :
    public Scene
{
public:
	Options();
	virtual ~Options() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:
	std::unique_ptr<MenuButton> myMuteSound;

	std::vector<std::unique_ptr<GameObject>> myButtons;
};

