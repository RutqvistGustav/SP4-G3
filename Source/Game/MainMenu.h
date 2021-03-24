#pragma once
#include "Scene.h"
#include <memory>

class MenuButton;

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
	void InitButtons();

	std::unique_ptr<MenuButton> myStartButton;
	std::unique_ptr<MenuButton> myQuitButton;
	std::unique_ptr<MenuButton> myOptionsButton;
	std::unique_ptr<MenuButton> myLevelSelectButton;

	std::vector<std::unique_ptr<GameObject>> myButtons;
};

