#pragma once

#include "MenuScene.h"

#include "Vector2.hpp"

#include <memory>

class MenuButton;
class SpriteWrapper;
class Slider;

class Settings :
	public MenuScene
{
public:

	Settings();
	virtual ~Settings() override;

	virtual void Init() override;

	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:

	void InitSprites();
	void InitSliders();
	void InitButtons();

	void SetResolution(int aResolutionY);
	void SetResolutionBool(int aResolutionY);
	void RenderResolutionText(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);
	void ChangeResolution(GameObjectTag aTag);

	void MouseClicked(GameObject* aTarget);

	void SetMasterVolume(float aVolume);
	void SetSfxVolume(float aVolume);
	void SetMusicVolume(float aVolume);

private:

	bool my720{};
	bool my900{};
	bool my1080{};

	CU::Vector2<float> myScreenResolution;

	std::shared_ptr<SpriteWrapper> my720Sprite;
	std::shared_ptr<SpriteWrapper> my900Sprite;
	std::shared_ptr<SpriteWrapper> my1080Sprite;

	std::vector<std::shared_ptr<SpriteWrapper>> mySprites;

};

