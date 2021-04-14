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


protected:
	virtual void ControllerControl(UpdateContext& anUpdateContext);
	void AddInterfaceElement(std::shared_ptr<GameObject> anElement);
	virtual void MouseClicked(GameObject* aTarget) = 0;
	virtual const bool CheckNext(UpdateContext& anUpdateContext)const;
	virtual const bool CheckPrev(UpdateContext& anUpdateContext)const;
	virtual void ControllerNavigate(UpdateContext& anUpdateContext);

protected:

	std::unique_ptr<MousePointer> myMousePointer;

	int myCurrentButtonIndex = 0;
	bool mySwitchingButton = false;

};
