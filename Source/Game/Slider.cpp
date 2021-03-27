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
	mySprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/slider zombie head.dds");
	mySprite->SetPanStrengthFactor(0);
	myBody->SetPanStrengthFactor(0);
	mySprite->SetPosition(myPosition);

	myCollider->Init(this, myPosition, 40.f);
	myCollider->SetBoxSize(CU::Vector2(mySprite->GetSize().x, mySprite->GetSize().y));
	myScene->GetCollisionManager()->AddCollider(myCollider);
}

void Slider::Update(const float aDeltaTime, UpdateContext& anUpdateContext, float aMousePosX)
{
	if (myMove)
	{
		Move(aMousePosX);
	}
	myPositionLastFrame = myPosition;
}

void Slider::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	RenderCommand renderCommand = RenderCommand(myBody);
	aRenderQueue->Queue(renderCommand);
	RenderCommand renderCommand2 = RenderCommand(mySprite);
	aRenderQueue->Queue(renderCommand2);
}

void Slider::SetPosition(const CU::Vector2<float> aPosition)
{
	myPosition = aPosition;
	mySprite->SetPosition(myPosition);

	const float offSetY = 6.f;
	myBody->SetPosition(CU::Vector2(myPosition.x, myPosition.y - offSetY));

	if (myCollider.get() != nullptr)
	{
		myCollider->SetPos(myPosition);
	}
}

void Slider::SetColliderSize(const CU::Vector2<float> aSize)
{
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

void Slider::Move(float aPosX)
{
	mySprite->SetPosition(CU::Vector2(aPosX, myPosition.y));
	myCollider->SetPos(CU::Vector2(aPosX, myPosition.y));
}
