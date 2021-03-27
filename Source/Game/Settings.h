#pragma once
#include "Scene.h"
#include <memory>
#include "Vector2.hpp"

class MenuButton;
class SpriteWrapper;
class TiledParser;
class TiledRenderer;
class TiledCollision;
class Slider;

class Settings :
	public Scene
{
public:
	Settings();
	virtual ~Settings() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:
	float myX{};
	float myY{};

	bool my720{};
	bool my900{};
	bool my1080{};

	CU::Vector2<float> myScreenResolution;

	void InitCollisions();
	void InitSprites();
	void InitSliders();
	void InitButtons();

	void SetPanFactors();

	void UpdateMouse(const float aDeltaTime, UpdateContext& anUpdateContext);
	void SetResolution();
	void RenderResolution(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);
	void ChangeResolution(GameObjectTag aTag);

	std::unique_ptr<TiledParser> myTiledParser;
	std::unique_ptr<TiledRenderer> myTiledRenderer;
	std::unique_ptr<TiledCollision> myTiledCollision;

	std::unique_ptr<MenuButton> myBackButton;
	std::unique_ptr<MenuButton> myLeftArrow;
	std::unique_ptr<MenuButton> myRightArrow;

	std::shared_ptr<SpriteWrapper> mySettingsSprite;
	std::shared_ptr<SpriteWrapper> myBackground;
	std::shared_ptr<SpriteWrapper> myResolutionSprite;
	std::shared_ptr<SpriteWrapper> my720Sprite;
	std::shared_ptr<SpriteWrapper> my900Sprite;
	std::shared_ptr<SpriteWrapper> my1080Sprite;
	std::shared_ptr<SpriteWrapper> myCurrentResolution;

	std::unique_ptr<Slider> myMasterVolume;
	std::unique_ptr<Slider> mySfxVolume;
	std::unique_ptr<Slider> myMusicVolume;

	std::vector<std::shared_ptr<SpriteWrapper>> mySprites;
	std::vector<std::shared_ptr<SpriteWrapper>> myResolutionSprites;
	std::vector<std::unique_ptr<MenuButton>> myButtons;
	std::vector<std::unique_ptr<Slider>> mySliders;
};

