#include "stdafx.h"
#include "GameObject.h"
#include "Collider.h"
#include "CollisionManager.h"

GameObject::GameObject()
{
	myCollider = nullptr;
}

GameObject::~GameObject()
{
	delete myCollider;
	myCollider = nullptr;
}

void GameObject::Init()
{
	myCollider = new Collider();
#ifdef _DEBUG
	myCollider->InitDebug();
#endif // _DEBUG

	CollisionManager::GetInstance()->AddCollider(myCollider);
}

void GameObject::Update(const float aDeltaTime)
{
	myCollider->SetPos(myPosition);
}

void GameObject::Render()
{
	// Render Wrapped Tga2D::CSprite;
}

const CU::Vector2<float>& GameObject::GetPosition() const
{
	return myPosition;
}

void GameObject::SetPosition(const CU::Vector2<float> aPosition)
{
	myPosition = aPosition;
}
