#include "stdafx.h"
#include "GameObject.h"

#include "Collider.h"
#include "CollisionManager.h"
#include "Scene.h"

#include "Scene.h"

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
	myCollider->Init(this, myPosition);
	myScene->GetCollisionManager()->AddCollider(myCollider);

	//mySprite = std::make_shared<SpriteWrapper>(SpriteWrapper(aSpritePath));
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
		myCollider->SetPos(myPosition);
	}
}

void GameObject::OnCollision(GameObject* /*aGameObject*/)
{
	switch (myCollider->GetCollisionStage())
	{
	case Collider::eCollisionStage::FirstFrame:
	case Collider::eCollisionStage::MiddleFrames:

#ifdef _DEBUG
		myCollider->setRenderColor(Tga2D::CColor(1.0f, 0.0f, 0.0f, 1.0f));
#endif // _DEBUG
		break;

	case Collider::eCollisionStage::NotColliding:
#ifdef _DEBUG
		myCollider->setRenderColor(Tga2D::CColor(1.0f, 1.0f, 1.0f, 1.0f));
#endif // _DEBUG
		break;
	default:
		break;
	}
}

void GameObject::OnCollision(TileType aTileType, CU::Vector2<float> anOffset)
{

}

const Collider* GameObject::GetCollider() const
{
	return myCollider.get();
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
