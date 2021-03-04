#include "stdafx.h"
#include "Collider.h"

#ifdef _DEBUG
#include <tga2d/sprite/sprite.h>
#endif // _DEBUG


Collider::Collider()
	: Collider(0.0f, 0.0f, 0.0f)
{}

Collider::Collider(CU::Vector2<float> aPos, float aRadius)
	: myPos(aPos)
	, myRadius(aRadius)
{
#ifdef _DEBUG
	myDebugSprite = nullptr;
#endif // _DEBUG
	if (aRadius < 0.1f)
	{
		myRadius = 0.1f;
	}

}

Collider::Collider(float aX, float aY, float aRadius)
	: Collider(CU::Vector2<float>(aX, aY), aRadius)
{}

Collider::~Collider()
{
#ifdef _DEBUG
	delete myDebugSprite;
	myDebugSprite = nullptr;
#endif // _DEBUG
}

void Collider::SetPos(const CU::Vector2<float> aPos)
{
	myPos = aPos;
}

bool Collider::GetCollision(const Collider* aCollider) const
{
	return (myPos - aCollider->myPos).Length() < myRadius + aCollider->myRadius;
}

#ifdef _DEBUG
void Collider::InitDebug()
{
	//myDebugSprite = new Tga2D::CSprite("debugCookie.png");
}

void Collider::RenderDebug()
{

	myDebugSprite->SetPosition({ myPos.x, myPos.y });
	myDebugSprite->SetSizeRelativeToScreen({ myRadius, myRadius });
	myDebugSprite->Render();

}
void Collider::setRenderColor(Tga2D::CColor aColor)
{

	myDebugSprite->SetColor(aColor);

}
#endif // _DEBUG

