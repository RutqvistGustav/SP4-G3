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
	myType = eObjectType::MousePointer;
	myScene = aScene;
	myCollider = std::make_shared<Collider>();
	myCollider->Init(this, myMousePointer);
	CollisionManager::GetInstance()->AddCollider(myCollider);

	mySprite = std::make_shared<SpriteWrapper>(SpriteWrapper("Sprites/Pointer.png"));
}

MousePointer::~MousePointer() = default;

void MousePointer::Update(float aDeltaTime, UpdateContext& anUpdateContext)
{	
	ReadingMouseCoordinates(anUpdateContext.myInput);
	ReadingLMBInput(anUpdateContext.myInput);

	myCollider->SetPos(myMousePointer);
	mySprite->SetPosition(myMousePointer);
}

void MousePointer::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	RenderCommand renderCommand = RenderCommand(mySprite);
	aRenderQueue->Queue(renderCommand);
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

void MousePointer::ReadingMouseCoordinates(CommonUtilities::Input* aInput)
{
	auto mousePos = aInput->GetMousePosition();

	myMousePointer = CU::Vector2(static_cast<float>(mousePos.myMouseX), static_cast<float>(mousePos.myMouseY));
}

void MousePointer::ReadingLMBInput(CommonUtilities::Input* aInput)
{
	if (myMouseButtonPressed == true)
		myClicked = false;

	if (aInput->IsKeyPressed(static_cast<int>(CommonUtilities::Input::EMouseKey::LEFT)) && myMouseButtonPressed == false)
	{
		myClicked = true;
		myMouseButtonPressed = true;
	}
	else if (aInput->IsKeyReleased(static_cast<int>(CommonUtilities::Input::EMouseKey::LEFT)))
	{
		myMouseButtonPressed = false;
	}
}