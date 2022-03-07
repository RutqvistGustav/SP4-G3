#pragma once

#include "Scene.h"
#include "IGameMessageSubscriber.h"

class InputInterface;

class MenuScene :
	public Scene,
	public IGameMessageSubscriber
{
public:
	MenuScene();
	virtual ~MenuScene() override;

	virtual void Init() override;

	virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;

	virtual GameMessageAction OnMessage(const GameMessage aMessage, const void* someMessageData) override;

protected:
	virtual void ControllerControl(const float aDeltaTime, UpdateContext& anUpdateContext);
	void AddInterfaceElement(std::shared_ptr<GameObject> anElement);
	virtual void MouseClicked(GameObject* aTarget) = 0;
	virtual const bool CheckNext(UpdateContext& anUpdateContext)const;
	virtual const bool CheckPrev(UpdateContext& anUpdateContext)const;
	virtual void ControllerNavigate(UpdateContext& anUpdateContext);

protected:

	std::unique_ptr<MousePointer> myMousePointer;

	int myButtonIndexClicked = 0;
	int myCurrentButtonIndex = 0;
	int myBackButtonIndex = -1;
	bool mySwitchingButton = false;
	bool myButtonClicked = false;
};
