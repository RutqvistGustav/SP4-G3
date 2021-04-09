#include "stdafx.h"
#include "Collider.h"
#include "GameObject.h"
#include "TiledCollision.h"
#include "TiledTile.h"
#include "TiledLayer.h"
#include "TiledMap.h"
#include "CollisionListener.h"

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


Collider::Collider() :
	Collider({}, { 256.0f, 256.0f })
{}

Collider::Collider(const CU::Vector2<float>& aPos, const CU::Vector2<float>& aSize) :
	myPos(aPos),
	mySize(aSize)
{

#ifdef _DEBUG
	myDebugSprite = nullptr;
#endif // _DEBUG
}

Collider::~Collider()
{
#ifdef _DEBUG
	/*delete myDebugSprite;
	myDebugSprite = nullptr;*/
#endif // _DEBUG
	myCollisionListener = nullptr;
}

void Collider::Init(const CU::Vector2<float>& aPos, const CU::Vector2<float>& aSize)
{
#ifdef _DEBUG
	InitDebug();
#endif // _DEBUG

	myPos = aPos;
	mySize = aSize;
}

void Collider::SetPosition(const CU::Vector2<float>& aPos)
{
	myPos = aPos;
}

void Collider::SetBoxSize(const CU::Vector2<float>& aSize)
{
	mySize = aSize;
}

const CU::Vector2<float>& Collider::GetBoxSize() const
{
	return mySize;
}

const CU::Vector2<float>& Collider::GetPosition() const
{
	return myPos;
}

AABB Collider::GetAABB() const
{
	return AABB::FromCenterAndSize(myPos, mySize);
}

const float Collider::GetWidth() const
{
	return mySize.x;
}

const float Collider::GetHight() const
{
	return mySize.y;
}

#ifdef _DEBUG
void Collider::InitDebug()
{
	// myDebugSprite = new Tga2D::CSprite("debugCookie.png");
}

void Collider::RenderDebug(RenderQueue* const aRenderQueue, RenderContext& /*aRenderContext*/)
{
	if (!myDoRender)
		return;

	myDebugSprite->SetPivot({ 0.5f, 0.5f });
	myDebugSprite->SetPosition({ myPos.x, myPos.y });
	myDebugSprite->SetSize(mySize);
	myDebugSprite->SetLayer(999);

	//ska användas i menyer
	// myDebugSprite->SetPanStrengthFactor(0);

	aRenderQueue->Queue(RenderCommand(myDebugSprite));

}
void Collider::setRenderColor(Tga2D::CColor aColor)
{

	myDebugSprite->SetColor(aColor);

}
#endif // _DEBUG

bool Collider::GetCollision(const Collider* aCollider)
{
	if (myPos.x - mySize.x * 0.5f < aCollider->myPos.x + aCollider->mySize.x * 0.5f &&
		myPos.x + mySize.x * 0.5f > aCollider->myPos.x - aCollider->mySize.x * 0.5f &&
		myPos.y - mySize.y * 0.5f < aCollider->myPos.y + aCollider->mySize.y * 0.5f &&
		myPos.y + mySize.y * 0.5f > aCollider->myPos.y - aCollider->mySize.y * 0.5f)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Collider::AddContact(const ContactKey& aContactKey)
{
	myContacts.push_back(aContactKey);
}

void Collider::RemoveContact(const ContactKey& aContactKey)
{
	auto it = std::find(myContacts.begin(), myContacts.end(), aContactKey);
	if (it != myContacts.end())
	{
		std::swap(myContacts.back(), *it);
		myContacts.pop_back();
	}
}

void Collider::ClearContacts()
{
	myContacts.clear();
}
