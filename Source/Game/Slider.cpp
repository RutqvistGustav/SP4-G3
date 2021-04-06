#include "stdafx.h"
#include "Slider.h"

#include "MousePointer.h"

#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"

#include "Collider.h"
#include "CollisionManager.h"
#include "CollisionInfo.h"

Slider::Slider(Scene* aScene, const char* aSpritePath, GameObjectTag aTag)
	: GameObject(aScene, aTag)
{
	SetTag(aTag);

	myBody = std::make_shared<SpriteWrapper>(aSpritePath);
}

Slider::~Slider() = default;

void Slider::Init()
{
	myLeftBoundry = myPosition.x * 0.9f;
	myRightBoundry = myPosition.x * 1.36f;

	mySprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/slider zombie head.dds");
	mySprite->SetPosition(myPosition);

	myCollider->Init(myPosition, mySprite->GetSize());
	myCollider->SetCollisionListener(this);
	myCollider->SetGameObject(this);

	myScene->GetCollisionManager()->AddCollider(myCollider);
}

void Slider::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	if (myMousePointer != nullptr)
	{
		myIsTrackingMouse = myIsTrackingMouse ? myMousePointer->IsMouseHeld() : myMousePointer->IsMouseDown();

		if (myIsTrackingMouse)
		{
			MoveWithMouse();
		}
		else
		{
			if (!myIsMouseOnSlider)
			{
				myMousePointer = nullptr;
			}
		}
	}
}

void Slider::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	aRenderQueue->Queue(RenderCommand(myBody));
	aRenderQueue->Queue(RenderCommand(mySprite));
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

void Slider::SetValueChangeCallback(const ValueChangeCallback& aValueChangeCallback)
{
	myValueChangeCallback = aValueChangeCallback;
}

void Slider::OnStay(const CollisionInfo& someCollisionInfo)
{
	GameObject* gameObject = someCollisionInfo.myOtherCollider->GetGameObject();
	assert(gameObject != nullptr);

	if (gameObject != nullptr && gameObject->GetTag() == GameObjectTag::MousePointer)
	{
		myMousePointer = static_cast<MousePointer*>(gameObject);
		myIsMouseOnSlider = true;
	}
}

void Slider::OnExit(const CollisionInfo& someCollisionInfo)
{
	GameObject* gameObject = someCollisionInfo.myOtherCollider->GetGameObject();
	assert(gameObject != nullptr);

	if (gameObject != nullptr && gameObject->GetTag() == GameObjectTag::MousePointer)
	{
		myIsMouseOnSlider = false;

		if (!myIsTrackingMouse)
		{
			myMousePointer = nullptr;
		}
	}
}

void Slider::MoveWithMouse()
{
	assert(myMousePointer != nullptr);

	const CU::Vector2<float> mousePosition = myMousePointer->GetPosition();

	const float newX = std::clamp(mousePosition.x, myLeftBoundry, myRightBoundry);
	const float targetPercentage = ComputeSlidePercentage(newX);

	SetSlidePercentage(targetPercentage);
}

void Slider::SetSlidePercentage(float aPercentage)
{
	const float actualPercentage = std::clamp(aPercentage, 0.0f, 1.0f);

	const float positionX = myLeftBoundry + (myRightBoundry - myLeftBoundry) * actualPercentage;

	SetPosition({ positionX, myPosition.y }, false);

	if (myValueChangeCallback)
	{
		myValueChangeCallback(actualPercentage);
	}
}

float Slider::ComputeSlidePercentage(const float aPositionX) const
{
	return (aPositionX - myLeftBoundry) / (myRightBoundry - myLeftBoundry);
}

float Slider::GetSlidePercentage() const
{
	return ComputeSlidePercentage(myPosition.x);
}
