#include "stdafx.h"
#include "Collider.h"
#include "GameObject.h"

#ifdef _DEBUG
#include <tga2d/sprite/sprite.h>
#endif // _DEBUG


Collider::Collider()
	: Collider(nullptr, 0.0f, 0.0f, 0.0f)
{}

Collider::Collider(GameObject* aGameObject, CU::Vector2<float> aPos, float aRadius)
	: myPos(aPos)
	, myRadius(aRadius)
	, myGameObject(aGameObject)
{

#ifdef _DEBUG
	myDebugSprite = nullptr;
#endif // _DEBUG
	if (aRadius < 0.01f)//temp
	{
		myRadius = 0.01f;
	}

}

Collider::Collider(GameObject* aGameObject, float aX, float aY, float aRadius)
	: Collider(aGameObject, CU::Vector2<float>(aX, aY), aRadius)
{}

Collider::~Collider()
{
#ifdef _DEBUG
	delete myDebugSprite;
	myDebugSprite = nullptr;
#endif // _DEBUG
}

void Collider::Init(GameObject* aGameObject, CU::Vector2<float> aPos, float aRadius)
{
	myGameObject = std::make_shared<GameObject>(*aGameObject);
	myPos = aPos;
	myRadius = aRadius;
}

void Collider::SetPos(const CU::Vector2<float> aPos)
{
	myPos = aPos;
}

bool Collider::GetCollision(const Collider* aCollider)
{
	if (myIsCube)
	{
		if (myPos.x + myRadius > aCollider->myPos.x - aCollider->myRadius &&
			myPos.x - myRadius < aCollider->myPos.x + aCollider->myRadius &&
			myPos.y + myRadius > aCollider->myPos.y - aCollider->myRadius &&
			myPos.y - myRadius < aCollider->myPos.y + aCollider->myRadius)
		{
			//AdvanceCollisionStage();
			return true;
		}
		else
		{
			return false;
		}
	}

	if ((myPos - aCollider->myPos).Length() < myRadius + aCollider->myRadius)
	{
		//AdvanceCollisionStage();
		return true;
	}
	else
	{
		return false;
	}
}

const std::shared_ptr<GameObject> Collider::GetGameObject() const
{
	return myGameObject;
}

const bool Collider::isColliding() const 
{ 
	return myIsColliding; 
}

#ifdef _DEBUG
void Collider::InitDebug()
{
	//myDebugSprite = new Tga2D::CSprite("debugCookie.png");
}

void Collider::RenderDebug()
{
	myDebugSprite->SetPivot({ 0.5f, 0.5f });
	myDebugSprite->SetPosition({ myPos.x, myPos.y });
	myDebugSprite->SetSizeRelativeToScreen({ myRadius * 4, myRadius * 4 });
	myDebugSprite->Render();

}
void Collider::setRenderColor(Tga2D::CColor aColor)
{

	myDebugSprite->SetColor(aColor);

}
#endif // _DEBUG

const Collider::eCollisionStage Collider::GetCollisionStage() const
{
	return myCollisionStage;
}

void Collider::AdvanceCollisionStage()
{
	myCollisionStage = static_cast<Collider::eCollisionStage>(static_cast<int>(myCollisionStage) + 1);
	if (myCollisionStage == Collider::eCollisionStage::Count)
	{
		myCollisionStage = Collider::eCollisionStage::NotColliding;
	}
}


