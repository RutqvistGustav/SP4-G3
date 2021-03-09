#include "stdafx.h"
#include "GameObject.h"

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
