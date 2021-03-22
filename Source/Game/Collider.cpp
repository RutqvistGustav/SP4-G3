#include "stdafx.h"
#include "Collider.h"
#include "GameObject.h"
#include "TiledCollision.h"
#include "TiledTile.h"
#include "TiledLayer.h"
#include "TiledMap.h"

#ifdef _DEBUG
#include <tga2d/sprite/sprite.h>
#endif // _DEBUG


Collider::Collider()
	: Collider(nullptr, 0.0f, 0.0f, 100.0f)
{}

Collider::Collider(GameObject* aGameObject, CU::Vector2<float> aPos, float aRadius)
	: myPos(aPos)
	, myGameObject(aGameObject)
{

#ifdef _DEBUG
	myDebugSprite = nullptr;
#endif // _DEBUG

	myDimentions.x = aRadius;
	myDimentions.y = aRadius;
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
	myDimentions.x = aRadius;
	myDimentions.y = aRadius;
}

void Collider::SetPos(const CU::Vector2<float> aPos)
{
	myPos = aPos;
}

bool Collider::GetCollision(const Collider* aCollider)
{

	if (myPos.x < aCollider->myPos.x + aCollider->myDimentions.x &&
		myPos.x + myDimentions.x > aCollider->myPos.x &&
		myPos.y < aCollider->myPos.y + aCollider->myDimentions.y &&
		myPos.y + myDimentions.y > aCollider->myPos.y)
	{
		//AdvanceCollisionStage();
		return true;
	}
	else
	{
		return false;
	}


	//if ((myPos - aCollider->myPos).Length() < myRadius + aCollider->myRadius)
	//{
	//	//AdvanceCollisionStage();
	//	return true;
	//}
	//else
	//{
	//	return false;
	//}
}

const TiledTile* Collider::GetCollision(const TiledCollision* aTiledCollision, CU::Vector2<float> anOffsetDirection)
{

	auto tileToCheck = aTiledCollision->GetTileAt(CU::Vector2<float>(myPos.x, myPos.y) + anOffsetDirection.GetNormalized() * GetRadius());


	if (tileToCheck != nullptr)
	{

		//if (box collider med tile(world pos & tile.dimensions) )


		/*if (myPos.x < aCollider->myPos.x + aCollider->myDimentions.x &&
			myPos.x + myDimentions.x > aCollider->myPos.x &&
			myPos.y < aCollider->myPos.y + aCollider->myDimentions.y &&
			myPos.y + myDimentions.y > aCollider->myPos.y)
		{

		}*/
		return tileToCheck;
	}
		return nullptr;
}

GameObject* Collider::GetGameObject() const
{
	return myGameObject;
}

//const bool Collider::isColliding() const
//{
//	return myIsColliding;
//}

void Collider::SetRadius(const float aRadius)
{
	myDimentions.x = aRadius * 2;
	myDimentions.y = aRadius * 2;
}

const float Collider::GetRadius() const
{
	return myDimentions.x * 0.5f;
}

const CU::Vector2<float> Collider::GetPosition() const
{
	return myPos;
}

const float Collider::GetWidth() const
{
	return myDimentions.x;
}

const float Collider::GetHight() const
{
	return myDimentions.y;
}

#ifdef _DEBUG
void Collider::InitDebug()
{
	//myDebugSprite = new Tga2D::CSprite("debugCookie.png");
}

void Collider::RenderDebug()
{
	myDebugSprite->SetPivot({ 0.5f, 0.5f });
	myDebugSprite->SetPosition({ myPos.x / (1280 * 1.5f), myPos.y / (720 * 1.5f) });
	myDebugSprite->SetSizeRelativeToScreen({ myDimentions.x / 400, myDimentions.y / 400 });
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

//const bool Collider::GetIsCube() const
//{
//	return myIsCube;
//}


