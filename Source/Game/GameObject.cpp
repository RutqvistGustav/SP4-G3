#include "stdafx.h"
#include "GameObject.h"
#include "Collider.h"
#include "CollisionManager.h"

GameObject::GameObject(float aX, float aY)
{
	myCollider = nullptr;
	myPosition.x = aX;
	myPosition.y = aY;
}

GameObject::~GameObject()
{
}

void GameObject::Init()
{

	myCollider = std::make_shared<Collider>();
	myCollider->Init(this, myPosition);
#ifdef _DEBUG
	myCollider->InitDebug();
#endif // _DEBUG

	CollisionManager::GetInstance()->AddCollider(myCollider);
}

void GameObject::Update(const float aDeltaTime)
{
	myCollider->SetPos(myPosition);
	myPositionLastFrame = myPosition;
}

void GameObject::Render()
{
	// Render Wrapped Tga2D::CSprite;
}
GameObject::GameObject(Scene* aScene)
	: myScene(aScene)
{}
GameObject::~GameObject() = default;

void GameObject::Update(const float /*aDeltaTime*/, UpdateContext& /*anUpdateContext*/)
{}

void GameObject::Render(RenderQueue* const /*aRenderQueue*/, RenderContext& /*aRenderContext*/)
{}

const CU::Vector2<float>& GameObject::GetPosition() const
{
	return myPosition;
}

void GameObject::SetPosition(const CU::Vector2<float> aPosition)
{
	myPosition = aPosition;
}

void GameObject::OnCollision(const GameObject* aGameObject)
{
	if (myIsPlayer)
	{
		switch (myCollider->GetCollisionStage())
		{
		case Collider::eCollisionStage::FirstFrame:
		case Collider::eCollisionStage::MiddleFrames:

			myPosition = myPositionLastFrame;
			myVelocity = CU::Vector2<float>();


			break;
		case Collider::eCollisionStage::NotColliding:


			break;
		default:
			break;
		}
		//myPosition = myPositionLastFrame;
		//myVelocity = CU::Vector2<float>();
	}
	else
	{
		
	}

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

void GameObject::OnFirstFrameCollision(const GameObject* aGameObject)
{
	if (myIsPlayer)
	{
		//myPosition = myPositionLastFrame;
		//myVelocity = CU::Vector2<float>();
	}
}

void GameObject::ResetOnGround()
{
}
