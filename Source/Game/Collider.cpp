#include "stdafx.h"
#include "Collider.h"
#include "GameObject.h"
#include "TiledCollision.h"
#include "TiledTile.h"
#include "TiledLayer.h"
#include "TiledMap.h"

#ifdef _DEBUG
#include <tga2d/sprite/sprite.h>
#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderContext.h"
#include "RenderCommand.h"
#include "Camera.h"
#include "Metrics.h"
#include "Scene.h"
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

	myDimentions.x = aRadius * 2;
	myDimentions.y = aRadius * 2;
}

Collider::Collider(GameObject* aGameObject, float aX, float aY, float aRadius)
	: Collider(aGameObject, CU::Vector2<float>(aX, aY), aRadius)
{}

Collider::~Collider()
{
#ifdef _DEBUG
	/*delete myDebugSprite;
	myDebugSprite = nullptr;*/
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
	myDimentions.x = aRadius * 2;
	myDimentions.y = aRadius * 2;
}

void Collider::SetPos(const CU::Vector2<float> aPos)
{
	myPos = aPos;
}

bool Collider::GetCollision(const Collider* aCollider)
{

	if (myPos.x - myDimentions.x * 0.5f < aCollider->myPos.x + aCollider->myDimentions.x * 0.5f &&
		myPos.x + myDimentions.x * 0.5f > aCollider->myPos.x - aCollider->myDimentions.x * 0.5f &&
		myPos.y - myDimentions.y * 0.5f < aCollider->myPos.y + aCollider->myDimentions.y * 0.5f &&
		myPos.y + myDimentions.y * 0.5f > aCollider->myPos.y - aCollider->myDimentions.y * 0.5f)
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

	auto tileToCheck = aTiledCollision->GetTileAt(CU::Vector2<float>(myPos.x, myPos.y) + anOffsetDirection.GetNormalized() * GetRadius() * 0.5f);


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

void Collider::SetBoxSize(const CU::Vector2<float> aSize)
{
	myDimentions.x = aSize.x;
	myDimentions.y = aSize.y;
}

CU::Vector2<float> Collider::GetBoxSize()
{
	return myDimentions;
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

void Collider::RenderDebug(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	if (!myDoRender)
		return;

	myDebugSprite->SetPivot({ 0.5f, 0.5f });
	myDebugSprite->SetPosition({ myPos.x, myPos.y });
	myDebugSprite->SetSize(myDimentions);

	//ska användas i menyer
	//myDebugSprite->SetPanStrengthFactor(0);

	aRenderQueue->Queue(RenderCommand(myDebugSprite));

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


