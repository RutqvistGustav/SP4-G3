#pragma once
#include "Scene.h"
#include <memory>

class MenuButton;
class TiledParser;
class TiledRenderer;
class TiledCollision;
class SpriteWrapper;

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
	std::unique_ptr<MenuButton> myLevelSelectButton;
	std::unique_ptr<MenuButton> mySettingsButton;
	std::unique_ptr<MenuButton> myCreditsButton;
	std::unique_ptr<MenuButton> myQuitButton;

	std::shared_ptr<SpriteWrapper> myBackground;

	std::vector<std::unique_ptr<MenuButton>> myButtons;

	std::unique_ptr<TiledParser> myTiledParser;
	std::unique_ptr<TiledRenderer> myTiledRenderer;
	std::unique_ptr<TiledCollision> myTiledCollision;
};

