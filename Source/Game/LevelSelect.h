#pragma once
#include "Scene.h"

class MenuButton;


class LevelSelect :
    public Scene
{
    LevelSelect();
    virtual ~LevelSelect() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:
	void InitButtons();

	std::unique_ptr<MenuButton> myLevel1;
	std::unique_ptr<MenuButton> myBackButton;
	
	std::vector<std::unique_ptr<MenuButton>> myButtons;

};

