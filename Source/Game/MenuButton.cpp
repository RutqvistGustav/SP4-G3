#include "stdafx.h"
#include "MenuButton.h"
#include "SpriteWrapper.h"
#include "RenderQueue.h"
#include "RenderCommand.h"
#include "Collider.h"

MenuButton::MenuButton(Scene* aScene, const char* aSpritePath, GameObjectTag aTag)
	: GameObject(aScene, aSpritePath)
{
	SetTag(aTag);
	mySprite->SetPanStrengthFactor(0);
}

MenuButton::~MenuButton() = default;

void MenuButton::Init()
{

}

void MenuButton::Update()
{
	myCollider->SetPos(myPosition);
	myPositionLastFrame = myPosition;
}

void MenuButton::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	RenderCommand renderCommand = RenderCommand(mySprite);
	aRenderQueue->Queue(renderCommand);
}

void MenuButton::SetPosition(const CU::Vector2<float> aPosition)
{
	myPosition = aPosition;
	mySprite->SetPosition(myPosition);
	if (myCollider.get() != nullptr)
	{
		myCollider->SetPos(myPosition);
	}
}