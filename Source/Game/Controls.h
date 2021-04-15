#pragma once

#include "MenuScene.h"

class SpriteWrapper;

class Controls
	: public MenuScene
{
public:

	enum class BackTarget
	{
		MainMenu,
		PauseMenu,
	};

	Controls(BackTarget aTarget = BackTarget::MainMenu);
	~Controls() = default;


	virtual void Init() override;

	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	void MouseClicked(GameObject* aTarget);

	inline bool IsActive() const { return myIsActive; }

private:

	bool myIsActive = true;
	BackTarget myBackTarget;

	std::vector<std::shared_ptr<SpriteWrapper>> mySprites;

};