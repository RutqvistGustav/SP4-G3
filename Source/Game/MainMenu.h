#pragma once
#include "Scene.h"

class GameObject;
class MousePointer;

class MainMenu :
    public Scene
{
public:
	MainMenu();
	virtual ~MainMenu() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

private:
	std::unique_ptr<GameObject> myStartButton;
	std::unique_ptr<GameObject> myQuitButton;
	std::unique_ptr<MousePointer> myMousePointer;

	std::vector<std::unique_ptr<GameObject>> myButtons;
};

