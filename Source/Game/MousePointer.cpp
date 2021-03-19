#include "stdafx.h"
#include "MousePointer.h"
#include "UpdateContext.h"
#include "InputManager.h"
#include "CoordinateHelper.h"
#include "CollisionManager.h"
#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"

MousePointer::MousePointer(Scene* aScene)
	: GameObject(aScene)
{
	myButtonClicked = false;
	myType = eObjectType::MousePointer;
	myScene = aScene;
	myCollider = std::make_shared<Collider>();
	myCollider->Init(this, myMousePointerPos);
	CollisionManager::GetInstance()->AddCollider(myCollider);

	mySprite = std::make_shared<SpriteWrapper>(SpriteWrapper("Sprites/Pointer.png"));
}

MousePointer::~MousePointer() = default;

void MousePointer::Update(float aDeltaTime, UpdateContext& anUpdateContext)
{	
	ReadingMouseCoordinates(aDeltaTime, anUpdateContext.myInput);
	ReadingLMBInput(anUpdateContext.myInputInterface);

	myCollider->SetPos(myMousePointerPos);
	mySprite->SetPosition(myMousePointerPos);
}

void MousePointer::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	RenderCommand renderCommand = RenderCommand(mySprite);
	aRenderQueue->Queue(renderCommand);
	myCollider->RenderDebug();
}

void MousePointer::OnCollision(GameObject* aGameObject)
{
	if (GetLMBDown())
	{
		myButtonClicked = true;
		myClickedButton = aGameObject->GetType();
	}
}

bool MousePointer::GetLMBDown()
{
	return myClicked;
}

bool MousePointer::ButtonClicked()
{
	return myButtonClicked;
}

GameObject::eObjectType MousePointer::ClickedButton()
{
	return myClickedButton;
}

void MousePointer::ReadingMouseCoordinates(float aDeltaTime, CommonUtilities::Input* aInput)
{
	auto mousePos = aInput->GetMousePosition();
	float mousX = static_cast<float>(mousePos.myMouseX);
	float mousY = static_cast<float>(mousePos.myMouseY);

	if (myLastPosCalculate == false)
	{
		myLastPosCalculate = true;
		myLastPos.x = mousX;
		myLastPos.y = mousY;
	}
	else
	{
		myTimer += aDeltaTime;
		if (myTimer >= 0.02f)
		{
			myTimer = {};
			myLastPosCalculate = false;			
			myDragPos = { myLastPos.x - mousX, myLastPos.y - mousY };
		}
	}

	myMousePointerPos = CU::Vector2(static_cast<float>(mousePos.myMouseX), static_cast<float>(mousePos.myMouseY));
	myMousePointerPos = CU::Vector2(myMousePointerPos.x * 1.5f, myMousePointerPos.y * 1.5f);
}

void MousePointer::ReadingLMBInput(InputInterface* aInputInterface)
{
	if (aInputInterface->IsShooting())
	{
		myClicked = true;
	}
	else
	{
		myClicked = false;
	}
}