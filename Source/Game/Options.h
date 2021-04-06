#pragma once

#include "Scene.h"

#include <memory>

class MenuButton;

class Options :
    public Scene
{
public:

	Options();
	virtual ~Options() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:

	void InitButtons();
	void MuteSound();

private:

	bool myIsMuted;
};

