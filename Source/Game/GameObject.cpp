#include "stdafx.h"
#include "GameObject.h"
#include "Collider.h"
#include "CollisionManager.h"

GameObject::GameObject(Scene* aScene, float aX, float aY)
	: GameObject(aScene)
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


	CollisionManager::GetInstance()->AddCollider(myCollider);
}


GameObject::GameObject(Scene* aScene)
	: myScene(aScene)
{
	/*myCollider = std::make_shared<Collider>();
	CollisionManager::GetInstance()->AddCollider(myCollider);*/
}

void GameObject::Update(const float /*aDeltaTime*/, UpdateContext& /*anUpdateContext*/)
{
	myCollider->SetPos(myPosition);
}

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
	CU::Vector2<float> fromOtherToMe(myPosition - aGameObject->myPosition);

	if (myIsPlayer)
	{
		switch (myCollider->GetCollisionStage())
		{
		case Collider::eCollisionStage::FirstFrame:
		case Collider::eCollisionStage::MiddleFrames:


			myPosition += fromOtherToMe.GetNormalized() *
				(myCollider->GetRadius() + aGameObject->myCollider->GetRadius() - fromOtherToMe.Length());


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

