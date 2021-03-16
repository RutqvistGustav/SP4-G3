#include "stdafx.h"
#include "MousePointer.h"
#include "UpdateContext.h"
#include "InputManager.h"
#include "CoordinateHelper.h"
#include "CollisionManager.h"
#include "SpriteWrapper.h"

MousePointer::MousePointer(Scene* aScene)
	: GameObject(aScene)
{
	myScene = aScene;
	myCollider = std::make_shared<Collider>();
	myCollider->Init(this, myPosition);
	CollisionManager::GetInstance()->AddCollider(myCollider);

	mySprite = std::make_shared<SpriteWrapper>(SpriteWrapper("Sprites/Pointer.png"));
}

MousePointer::~MousePointer() = default;

void MousePointer::Update(float aDeltaTime, UpdateContext& anUpdateContext)
{	
	ReadingMouseCoordinates(aDeltaTime, anUpdateContext.myInput);
	ReadingLMBInput(anUpdateContext.myInput);
}

void MousePointer::OnCollision(GameObject* aGameObject)
{
	
}

bool MousePointer::GetLMBDown()
{
	return myClickIsTrue;
}

CU::Vector2<float> MousePointer::GetMouseCoordinates()
{
	return myMousePointer;
}

CU::Vector2<float> MousePointer::GetMouseDrag()
{
	return myDragPos;
}

void MousePointer::ReadingMouseCoordinates(float aDeltaTime, CommonUtilities::Input* aInput)
{
	auto mousePos = aInput->GetMousePosition();

	if (myLastPosCalculate == false)
	{
		myLastPosCalculate = true;
		myLastPos.x = static_cast<float>(mousePos.myMouseX);
		myLastPos.y = static_cast<float>(mousePos.myMouseY);
	}
	else
	{
		myTimer += aDeltaTime;
		if (myTimer >= 0.02f)
		{
			myTimer = {};
			myLastPosCalculate = false;
			CU::Vector2<float> currentPos = { static_cast<float>(mousePos.myMouseX), static_cast<float>(mousePos.myMouseY) };
			myDragPos = { myLastPos.x - currentPos.x, myLastPos.y - currentPos.y };
		}
	}


	myMousePointer.x = static_cast<float>(mousePos.myMouseX);
	myMousePointer.y = static_cast<float>(mousePos.myMouseY);

	myMousePointer = CoordinateHelper::GetClientPositionAsVirtual(myMousePointer);
}

void MousePointer::ReadingLMBInput(CommonUtilities::Input* aInput)
{
	if (myButtonPress == true)
		myClickIsTrue = false;

	if (aInput->IsKeyPressed(static_cast<int>(CommonUtilities::Input::EMouseKey::LEFT)) && myButtonPress == false)
	{
		myClickIsTrue = true;
		myButtonPress = true;

	}
	else if (aInput->IsKeyReleased(static_cast<int>(CommonUtilities::Input::EMouseKey::LEFT)))
	{
		myButtonPress = false;
	}
}