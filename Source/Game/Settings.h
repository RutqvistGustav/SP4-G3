#pragma once

#include "MenuScene.h"

#include "Vector2.hpp"

#include <memory>

class MenuButton;
class SpriteWrapper;
class TextWrapper;
class Slider;

class Settings :
	public MenuScene
{
public:
	enum class eBackTarget
	{
		ePauseMenu,
		eMainMenu
	};

	struct Resolution
	{
		int myWidth;
		int myHeight;

		friend bool operator==(const Resolution& aMe, const Resolution& anOther)
		{
			return aMe.myWidth == anOther.myWidth && aMe.myHeight == anOther.myHeight;
		}

		friend bool operator<(const Resolution& aMe, const Resolution& anOther)
		{
			int mySize = aMe.myWidth * aMe.myHeight;
			int otherSize = anOther.myWidth * anOther.myHeight;

			return mySize < otherSize;
		}
	};

	Settings();
	Settings(eBackTarget aTarget);
	virtual ~Settings() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	bool IsSettingsActive();

private:

	void FindAvailableResolutions();

	void DetectResolution();

	void InitSprites();
	void InitSliders();
	void InitButtons();

	void SetResolutionIndex(int anIndex, bool anUpdateResolution);

	void SlideResolution(int anAmount);

	void RenderResolutionText(RenderQueue* const aRenderQueue, RenderContext& aRenderContext);

	void MouseClicked(GameObject* aTarget);

	void SetMasterVolume(float aVolume);
	void SetSfxVolume(float aVolume);
	void SetMusicVolume(float aVolume);

	//void ControllerNavigate(UpdateContext& anUpdateContext) override;
	void ControllerControl(const float aDeltaTime, UpdateContext& anUpdateContext) override;

private:
	bool myIsActive = true;
	eBackTarget myBackTarget;

	VECTOR2UI myPrevDetectedResolution;

	std::shared_ptr<TextWrapper> myResolutionText;
	std::vector<Resolution> myResolutions;
	int myCurrentResolutionIndex;

	std::vector<std::shared_ptr<SpriteWrapper>> mySprites;

};

