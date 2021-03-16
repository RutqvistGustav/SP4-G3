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
	, myGameObject(aGameObject)
{

#ifdef _DEBUG
	myDebugSprite = nullptr;
#endif // _DEBUG

	SetRadius(aRadius);
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
	myGameObject = nullptr;
}

void Collider::Init(GameObject* aGameObject, CU::Vector2<float> aPos, float aRadius)
{
#ifdef _DEBUG
	InitDebug();
#endif // _DEBUG

	myGameObject = aGameObject;
	//myGameObject = std::shared_ptr<GameObject>(aGameObject);
	myPos = aPos;
	SetRadius(aRadius);
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

GameObject* Collider::GetGameObject() const
{
	return myGameObject;
}

const bool Collider::isColliding() const
{
	return myIsColliding;
}

void Collider::SetRadius(const float aRadius)
{
	if (aRadius < 100.f)//temp
	{
		myRadius = 100.f;
	}
	else
	{
		myRadius = aRadius;
	}

}

const float Collider::GetRadius() const
{
	return myRadius;
}

#ifdef _DEBUG
void Collider::InitDebug()
{
	//myDebugSprite = new Tga2D::CSprite("debugCookie.png");
}

void Collider::RenderDebug()
{
	myDebugSprite->SetPivot({ 0.5f, 0.5f });
	myDebugSprite->SetPosition({ myPos.x / (1280*1.5f), myPos.y / (720* 1.5f)});
	myDebugSprite->SetSizeRelativeToScreen({ myRadius / 400, myRadius / 400 });
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

//const Collider::eCollisionType Collider::GetCollisionType() const
//{
//	return myCollitionType;
//}
//
//void Collider::SetCollitionType(const eCollisionType aCollitionType)
//{
//	myCollitionType = aCollitionType;
//}

void Collider::AdvanceCollisionStage()
{
	myCollisionStage = static_cast<Collider::eCollisionStage>(static_cast<int>(myCollisionStage) + 1);
	if (myCollisionStage == Collider::eCollisionStage::Count)
	{
		myCollisionStage = Collider::eCollisionStage::NotColliding;
	}
}

const bool Collider::GetIsCube() const
{
	return myIsCube;
}


