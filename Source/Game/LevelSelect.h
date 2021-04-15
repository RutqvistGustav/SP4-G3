#pragma once

#include "MenuScene.h"

#include <memory>

class MenuButton;
class SpriteWrapper;

class LevelSelect :
    public MenuScene
{
public:

	LevelSelect();
    virtual ~LevelSelect() override;

	virtual void Init() override;

	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:

	void InitButtons();

	void MouseClicked(GameObject* aTarget);

	void ControllerControl(const float aDeltaTime, UpdateContext& anUpdateContext) override;

	const bool CheckNext(UpdateContext& anUpdateContext)const override;
	const bool CheckPrev(UpdateContext& anUpdateContext)const override;
	virtual void ControllerNavigate(UpdateContext& anUpdateContext) override;

private:

	std::shared_ptr<SpriteWrapper> myBackground;
	bool myOnBackButton = false;

};
