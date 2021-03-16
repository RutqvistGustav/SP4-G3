#pragma once
#include "GameObject.h"

namespace CommonUtilities
{
	class Input;
}

class SpriteWrapper;

class MousePointer :
    public GameObject
{
public:
	MousePointer(Scene* aScene);
	virtual ~MousePointer() override;

    virtual void Update(const float aDeltaTime, UpdateContext& anUpdateContext) override;
	virtual void Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext) override;
	void OnCollision(GameObject* aGameObject) override;

	bool GetLMBDown();
	bool ButtonClicked();
	GameObject::eObjectType ClickedButton();

private:

	CU::Vector2<float> myMousePointer;

	bool myClicked;
	bool myMouseButtonPressed;
	bool myButtonClicked;
	GameObject::eObjectType myClickedButton;

	void ReadingMouseCoordinates(CommonUtilities::Input* aInput);
	void ReadingLMBInput(CommonUtilities::Input* aInput);
};