#include "stdafx.h"
#include "Slider.h"
#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"
#include "Collider.h"
#include "CollisionManager.h"
#include "MousePointer.h"

Slider::Slider(Scene* aScene, const char* aSpritePath, GameObjectTag aTag)
	: GameObject(aScene, aTag)
{
	SetTag(aTag);
	myScene = aScene;
	myBody = std::make_shared<SpriteWrapper>(aSpritePath);
	myMove = false;
}

Slider::~Slider() = default;

void Slider::Init()
{
	myLeftBoundry = myPosition.x * 0.9f;
	myRightBoundry = myPosition.x * 1.36f;

	mySprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/slider zombie head.dds");
	mySprite->SetPanStrengthFactor(0);
	myBody->SetPanStrengthFactor(0);
	SetVolumePos();
	mySprite->SetPosition(myPosition);

	//myCollider->Init(this, myPosition, 40.f);
	myCollider->SetBoxSize(CU::Vector2(mySprite->GetSize().x, mySprite->GetSize().y));
	myScene->GetCollisionManager()->AddCollider(myCollider);
}

void Slider::Update(const float aDeltaTime, UpdateContext& anUpdateContext, bool aLMBDown, CU::Vector2<float> aMousePos)
{
	//if (myMove)
	//{
	//	Move(aMousePosX);
	//}
	if (aLMBDown)
	{
		ClickedMove(aMousePos);
	}

	myPositionLastFrame = myPosition;
	CalculateVolume();
}

void Slider::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	RenderCommand renderCommand = RenderCommand(myBody);
	aRenderQueue->Queue(renderCommand);
	RenderCommand renderCommand2 = RenderCommand(mySprite);
	aRenderQueue->Queue(renderCommand2);
}

void Slider::SetPosition(const CU::Vector2<float> aPosition, bool aSetBodyPos)
{
	myPosition = aPosition;
	mySprite->SetPosition(myPosition);

	const float offSetY = 6.f;

	if (aSetBodyPos)
	{
		myBody->SetPosition(CU::Vector2(myPosition.x, myPosition.y - offSetY));
	}

	if (myCollider.get() != nullptr)
	{
		myCollider->SetPosition(myPosition);
	}
}

void Slider::SetColliderSize(const CU::Vector2<float> aSize)
{
}

void Slider::SetVolumePos()
{
	float volume = .5f;

	myPosition.x = (myRightBoundry - myLeftBoundry) * volume + myLeftBoundry;
}

void Slider::CalculateVolume()
{
	float volume =  myPosition.x / (myRightBoundry + myLeftBoundry);
}

void Slider::OnCollision(GameObject* aGameObject)
{
	if (aGameObject->GetTag() == GameObjectTag::MousePointer)
	{
		MousePointer* mousePointer = static_cast<MousePointer*>(aGameObject);
		
		if (mousePointer->GetLMBDown())
		{
			myMove = true;
		}
	}
}

void Slider::PressedMove(float aPosX)
{
	if (aPosX >= myLeftBoundry && aPosX <= myRightBoundry)
	{
		mySprite->SetPosition(CU::Vector2(aPosX, myPosition.y));
		myCollider->SetPosition(CU::Vector2(aPosX, myPosition.y));
	}
}

void Slider::ClickedMove(CU::Vector2<float> aMousePos)
{
	const float y = myCollider->GetBoxSize().y;
	const float offSetX = 35.f;

	if (aMousePos.x >= myLeftBoundry - offSetX && aMousePos.x <= myRightBoundry + offSetX &&
		aMousePos.y <= myPosition.y + (y * 0.5f) && aMousePos.y >= myPosition.y - (y * 0.5f))
	{
		if (aMousePos.x <= myLeftBoundry)
		{
			myPosition.x = myLeftBoundry;
		}
		else if (aMousePos.x >= myRightBoundry)
		{
			myPosition.x = myRightBoundry;
		}
		else
		{
			myPosition.x = aMousePos.x;
		}

		SetPosition(myPosition, false);
	}
}
