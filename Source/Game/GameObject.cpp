#include "stdafx.h"
#include "GameObject.h"

#include "Collider.h"
#include "CollisionManager.h"

#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"

GameObject::GameObject(Scene* aScene, const char* aSpritePath) :
	GameObject(aScene, GameObjectTag::Default, aSpritePath)
{}

GameObject::GameObject(Scene* aScene, GameObjectTag aTag, const char* aSpritePath) :
	myScene(aScene),
	myTag(aTag)
{
	myCollider = std::make_shared<Collider>();
	mySprite = std::make_shared<SpriteWrapper>(aSpritePath);
}

GameObject::~GameObject()
{
	if (myCollider != nullptr)
	{
		myScene->GetCollisionManager()->RemoveCollider(myCollider);
	}
}

void GameObject::Init()
{
	myCollider->Init(myPosition, mySprite->GetSize());
	myCollider->SetCollisionListener(this);
	myCollider->SetGameObject(this);

	myScene->GetCollisionManager()->AddCollider(myCollider);
}

void GameObject::Update(const float /*aDeltaTime*/, UpdateContext& /*anUpdateContext*/)
{
	myPositionLastFrame = myPosition;
}

void GameObject::Render(RenderQueue* const aRenderQueue, RenderContext& /*aRenderContext*/)
{
	aRenderQueue->Queue(RenderCommand(mySprite));
}

const CU::Vector2<float>& GameObject::GetPosition() const
{
	return myPosition;
}

void GameObject::SetPosition(const CU::Vector2<float> aPosition)
{
	myPosition = aPosition;
	mySprite->SetPosition(myPosition);

	if (myCollider.get() != nullptr)
	{
		myCollider->SetPosition(myPosition);
	}

	if (myPositionLastFrame.x + myPositionLastFrame.y == 0.0f)
	{
		myPositionLastFrame = myPosition;
	}
}

const Collider* GameObject::GetCollider() const
{
	return myCollider.get();
}

void GameObject::RemoveCollider()
{
	myScene->GetCollisionManager()->RemoveCollider(myCollider);
	myCollider.reset();
}

GlobalServiceProvider* GameObject::GetGlobalServiceProvider()
{
	return GetScene()->GetGlobalServiceProvider();
}

bool GameObject::GetDeleteThisFrame()
{
	return myDeleteThisFrame;
}

void GameObject::SetDeleteThisFrame()
{
	myDeleteThisFrame = true;
}
