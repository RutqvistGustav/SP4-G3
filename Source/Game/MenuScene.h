#pragma once

#include "Scene.h"

class InputInterface;

class MenuScene :
	public Scene
{
public:

	MenuScene();
	virtual ~MenuScene() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	void ControllerControl(UpdateContext& anUpdateContext);

protected:

	void AddInterfaceElement(std::shared_ptr<GameObject> anElement);
	virtual void MouseClicked(GameObject* aTarget) = 0;

protected:

	std::unique_ptr<MousePointer> myMousePointer;

	int myCurrentButtonIndex = 0;
	bool mySwitchingButton = false;

};
