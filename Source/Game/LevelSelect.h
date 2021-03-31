#pragma once
#include "Scene.h"
#include <memory>

class MenuButton;
class SpriteWrapper;
class TiledParser;
class TiledRenderer;
class TiledCollision;

class LevelSelect :
    public Scene
{
public:
    LevelSelect();
    virtual ~LevelSelect() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:
	float myX{};
	float myY{};

	std::unique_ptr<MenuButton> myLevel1;
	std::unique_ptr<MenuButton> myLevel2;
	std::unique_ptr<MenuButton> myLevel3;

	std::unique_ptr<MenuButton> myBackButton;
	
	std::unique_ptr<TiledParser> myTiledParser;
	std::unique_ptr<TiledRenderer> myTiledRenderer;
	std::unique_ptr<TiledCollision> myTiledCollision;

	std::shared_ptr<SpriteWrapper> myBackground;

	std::vector<std::unique_ptr<MenuButton>> myButtons;
	std::vector<std::shared_ptr<SpriteWrapper>> mySprites;

	void InitCollisions();
	void InitSprites();
	void InitButtons();

	void SetPanFactors();

	void UpdateObjects();
	void UpdateMouse(const float aDeltaTime, UpdateContext& anUpdateContext);

	void RenderObjects(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);
};

