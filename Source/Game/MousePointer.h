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
	void OnCollision(GameObject* aGameObject) override;

	//void ActivateMouse(bool aActivation);
	bool GetLMBDown();
	CU::Vector2<float> GetMouseCoordinates();
	CU::Vector2<float> GetMouseDrag();

private:

	CU::Vector2<float> myMousePointer;
	CU::Vector2<float> myLastPos;
	CU::Vector2<float> myDragPos;

	float myTimer;

	bool myLastPosCalculate;
	bool myClickIsTrue;
	bool myButtonPress;

	void ReadingMouseCoordinates(float aDeltaTime, CommonUtilities::Input* aInput);
	void ReadingLMBInput(CommonUtilities::Input* aInput);
};