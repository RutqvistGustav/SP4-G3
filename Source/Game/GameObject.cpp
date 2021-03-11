#include "stdafx.h"
#include "GameObject.h"

#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"

GameObject::GameObject(Scene* aScene, const char* aSpritePath)
	: myScene(aScene)
{
	mySprite = std::make_shared<SpriteWrapper>(SpriteWrapper(aSpritePath));
}
GameObject::~GameObject() = default;

void GameObject::Update(const float /*aDeltaTime*/, UpdateContext& /*anUpdateContext*/)
{}

void GameObject::Render(RenderQueue* const aRenderQueue, RenderContext& /*aRenderContext*/)
{
	RenderCommand renderCommand = RenderCommand(mySprite);
	aRenderQueue->Queue(renderCommand);
}

const CU::Vector2<float>& GameObject::GetPosition() const
{
	return myPosition;
}

void GameObject::SetPosition(const CU::Vector2<float> aPosition)
{
	myPosition = aPosition;
	mySprite->SetPosition(myPosition);
}