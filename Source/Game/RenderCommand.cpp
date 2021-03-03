#include "stdafx.h"
#include "RenderCommand.h"

#include "SpriteWrapper.h"

RenderCommand::RenderCommand(const std::shared_ptr<SpriteWrapper> aSprite)
{
	Init(aSprite);
}

RenderCommand::~RenderCommand()
{
	Reset();
}

void RenderCommand::Init(const std::shared_ptr<SpriteWrapper> aSprite)
{
	Reset();

	myType = RenderObjectType::Sprite;
	myLayer = aSprite->GetLayer();

	new (&mySpriteRenderData) SpriteRenderData(aSprite->myRenderData);
}

void RenderCommand::Reset()
{
	// TODO: If the active render data object has a destructor we need to call it here

	myType = RenderObjectType::Unknown;
}
