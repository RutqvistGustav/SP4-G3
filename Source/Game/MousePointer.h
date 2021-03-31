#pragma once
#include "GameObject.h"

namespace CommonUtilities
{
	class Input;
}

class SpriteWrapper;
class InputInterface;

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
	bool GetButtonClicked();
	void SetButtonClicked(bool aBool);
	CU::Vector2<float> GetPointerPos();
	GameObjectTag ClickedButton() const;

private:

	CU::Vector2<float> myMousePointerPos;
	CU::Vector2<float> myLastPos;
	CU::Vector2<float> myDragPos;

	float myTimer;
	bool myLastPosCalculate;
	bool myClicked;
	bool myButtonClicked;
	GameObjectTag myClickedButton;

	void ReadingMouseCoordinates(float aDeltaTime, CommonUtilities::Input* aInput);
	void ReadingLMBInput(InputInterface* aInputInterface);
};