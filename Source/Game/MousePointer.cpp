#include "stdafx.h"
#include "MousePointer.h"
#include "UpdateContext.h"
#include "InputManager.h"
#include "CoordinateHelper.h"
#include "CollisionManager.h"
#include "CollisionInfo.h"
#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"
#include "Metrics.h"

MousePointer::MousePointer(Scene* aScene)
	: GameObject(aScene)
{
	myButtonClicked = false;
	SetTag(GameObjectTag::MousePointer);
	myScene = aScene;
	myCollider = std::make_shared<Collider>();
	myCollider->Init(myMousePointerPos, { 5.0f, 5.0f });
	myCollider->SetCollisionListener(this);
	myCollider->SetGameObject(this);
	myScene->GetCollisionManager()->AddCollider(myCollider);

	mySprite = std::make_shared<SpriteWrapper>(SpriteWrapper("Sprites/Menue UI/ProgArt/Pointer.png"));
	mySprite->SetPanStrengthFactor(0);
}

MousePointer::~MousePointer() = default;

void MousePointer::Update(float aDeltaTime, UpdateContext& anUpdateContext)
{	
	ReadingMouseCoordinates(aDeltaTime, anUpdateContext.myInput);
	ReadingLMBInput(anUpdateContext.myInputInterface);

	myCollider->SetPosition(myMousePointerPos);
	mySprite->SetPosition(myMousePointerPos);
}

void MousePointer::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	//float x = Metrics::GetReferenceSize().x;
	//float y = Metrics::GetReferenceSize().y;
	//const float offSet = 1.5f;

	//if (myMousePointerPos.x <= offSet || myMousePointerPos.x >= x - offSet ||
	//	myMousePointerPos.y <= offSet || myMousePointerPos.y >= y - offSet)
	//{
	//	return;
	//}

	//RenderCommand renderCommand = RenderCommand(mySprite);
	//aRenderQueue->Queue(renderCommand);
	myCollider->RenderDebug(aRenderQueue, aRenderContext);
}

bool MousePointer::GetLMBDown()
{
	return myClicked;
}

bool MousePointer::GetButtonClicked()
{
	return myButtonClicked;
}

void MousePointer::SetButtonClicked(bool aBool)
{
	myButtonClicked = aBool;
}

CU::Vector2<float> MousePointer::GetPointerPos()
{
	return myMousePointerPos;
}

GameObjectTag MousePointer::ClickedButton() const
{
	return myClickedButton;
}

void MousePointer::OnStay(const CollisionInfo& someCollisionInfo)
{
	if (GetLMBDown())
	{
		myButtonClicked = true;

		GameObject* buttonObject = someCollisionInfo.myOtherCollider->GetGameObject();
		if (buttonObject != nullptr)
		{
			myClickedButton = buttonObject->GetTag();
		}
	}
}

void MousePointer::ReadingMouseCoordinates(float aDeltaTime, CommonUtilities::Input* aInput)
{
	auto mousePos = aInput->GetMousePosition();
	auto refSize = Metrics::GetReferenceSize();
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
	myMousePointerPos = CoordinateHelper::GetClientPositionAsVirtual(CU::Vector2(mousX, mousY));
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
