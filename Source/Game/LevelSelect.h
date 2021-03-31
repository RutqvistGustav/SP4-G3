#pragma once
#include "Scene.h"
#include <memory>

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
	std::unique_ptr<MenuButton> myLevel2;
	std::unique_ptr<MenuButton> myLevel3;
	std::unique_ptr<MenuButton> myLevel4;
	std::unique_ptr<MenuButton> myLevel5;
	std::unique_ptr<MenuButton> myLevel6;
	std::unique_ptr<MenuButton> myLevel7;
	std::unique_ptr<MenuButton> myLevel8;
	std::unique_ptr<MenuButton> myLevel9;
	std::unique_ptr<MenuButton> myBackButton;
	
	std::vector<std::unique_ptr<MenuButton>> myButtons;

};

