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

private:

	std::shared_ptr<SpriteWrapper> myBackground;

};
