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

	enum class Resolution
	{
		R1280x720,
		R1600x900,
		R1920x1080,

		Count,
	};

	Settings();
	virtual ~Settings() override;

	virtual void Init() override;

	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:

	void InitSprites();
	void InitSliders();
	void InitButtons();

	void SetResolution(Resolution aResolution);
	void SlideResolution(int anAmount);

	void RenderResolutionText(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	void MouseClicked(GameObject* aTarget);

	void SetMasterVolume(float aVolume);
	void SetSfxVolume(float aVolume);
	void SetMusicVolume(float aVolume);

private:

	Resolution myResolution{ Resolution::R1920x1080 };

	std::shared_ptr<SpriteWrapper> my720Sprite;
	std::shared_ptr<SpriteWrapper> my900Sprite;
	std::shared_ptr<SpriteWrapper> my1080Sprite;

	std::vector<std::shared_ptr<SpriteWrapper>> mySprites;

};

