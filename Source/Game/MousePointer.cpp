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
#include "CollisionInfo.h"

MousePointer::MousePointer(Scene* aScene)
	: GameObject(aScene, "Sprites/Menue UI/ProgArt/Pointer.png")
{
	SetTag(GameObjectTag::MousePointer);
}

MousePointer::~MousePointer() = default;

void MousePointer::Update(float aDeltaTime, UpdateContext& anUpdateContext)
{	
	ReadingMouseCoordinates(aDeltaTime, anUpdateContext.myInput);
	ReadingLMBInput(anUpdateContext.myInputInterface);
}

void MousePointer::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	myCollider->RenderDebug(aRenderQueue, aRenderContext);
}

void MousePointer::SetClickCallback(const ClickCallback& aClickCallback)
{
	myClickCallback = aClickCallback;
}

void MousePointer::OnStay(const CollisionInfo& someCollisionInfo)
{
	if (IsMouseDown())
	{
		GameObject* gameObject = someCollisionInfo.myOtherCollider->GetGameObject();
		if (myClickCallback)
		{
			myClickCallback(gameObject);
		}
	}
}

bool MousePointer::IsMouseDown()
{
	return myMouseDown;
}

bool MousePointer::IsMouseHeld()
{
	return myMouseHeld;
}

void MousePointer::ReadingMouseCoordinates(float aDeltaTime, CommonUtilities::Input* aInput)
{
	auto mousePos = aInput->GetMousePosition();
	const CU::Vector2<float> mousePosition = { static_cast<float>(mousePos.myMouseX), static_cast<float>(mousePos.myMouseY) };

	SetPosition(CoordinateHelper::GetClientPositionAsVirtual(mousePosition));
}

void MousePointer::ReadingLMBInput(InputInterface* aInputInterface)
{
	const bool isMouseDown = aInputInterface->IsHoldingMenuAccept();
	myMouseDown = !myMouseHeld && isMouseDown;
	myMouseHeld = isMouseDown;
}
