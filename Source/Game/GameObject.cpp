#include "stdafx.h"
#include "GameObject.h"

GameObject::~GameObject()
{

}

void GameObject::Update(const float aDeltaTime)
{
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
