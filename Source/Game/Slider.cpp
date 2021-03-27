#include "stdafx.h"
#include "Slider.h"
#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"
#include "Collider.h"
#include "CollisionManager.h"

Slider::Slider(Scene* aScene, const char* aSpritePath, GameObjectTag aTag)
	: GameObject(aScene, aTag)
{
	SetTag(aTag);
	myScene = aScene;
	myBody = std::make_shared<SpriteWrapper>(aSpritePath);
}

Slider::~Slider() = default;

void Slider::Init()
{
	mySprite = std::make_shared<SpriteWrapper>("Sprites/Menue UI/settings/slider zombie head.dds");
	mySprite->SetPanStrengthFactor(0);
	myBody->SetPanStrengthFactor(0);
	
	myCollider->Init(this, myPosition, 40.f);
	myCollider->SetBoxSize(CU::Vector2(mySprite->GetSize().x, mySprite->GetSize().y));
	myScene->GetCollisionManager()->AddCollider(myCollider);
}

void Slider::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myPositionLastFrame = myPosition;
}

void Slider::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	RenderCommand renderCommand = RenderCommand(myBody);
	aRenderQueue->Queue(renderCommand);
	renderCommand = RenderCommand(mySprite);
	aRenderQueue->Queue(renderCommand);
	myCollider->RenderDebug(aRenderQueue, aRenderContext);
}

void Slider::SetPosition(const CU::Vector2<float> aPosition)
{
	myPosition = aPosition;
	mySprite->SetPosition(myPosition);
	myBody->SetPosition(myPosition);

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
}
