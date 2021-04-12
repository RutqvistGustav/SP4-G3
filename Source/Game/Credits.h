#pragma once

#include "MenuScene.h"

class SpriteWrapper;

class Credits
	: public MenuScene
{
public:
	Credits () = default;
	~Credits () = default;


	virtual void Init() override;

	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	void MouseClicked(GameObject* aTarget);
private:

	std::vector<std::shared_ptr<SpriteWrapper>> mySprites;

};