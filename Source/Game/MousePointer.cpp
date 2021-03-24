#include "stdafx.h"
#include "MousePointer.h"
#include "UpdateContext.h"
#include "InputManager.h"
#include "CoordinateHelper.h"
#include "CollisionManager.h"
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
	myCollider->Init(this, myMousePointerPos);
	myScene->GetCollisionManager()->AddCollider(myCollider);

	mySprite = std::make_shared<SpriteWrapper>(SpriteWrapper("Sprites/Menue UI/ProgArt/Pointer.png"));
	mySprite->SetPanStrengthFactor(0);
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
	float x = Metrics::GetReferenceSize().x;
	float y = Metrics::GetReferenceSize().y;
	const float offSet = 1.5f;

	if (myMousePointerPos.x <= offSet || myMousePointerPos.x >= x - offSet ||
		myMousePointerPos.y <= offSet || myMousePointerPos.y >= y - offSet)
	{
		return;
	}

	RenderCommand renderCommand = RenderCommand(mySprite);
	aRenderQueue->Queue(renderCommand);
}

void MousePointer::OnCollision(GameObject* aGameObject)
{
	if (GetLMBDown())
	{
		myButtonClicked = true;
		myClickedButton = aGameObject->GetTag();
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

GameObjectTag MousePointer::ClickedButton() const
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