#include "stdafx.h"
#include "RenderCommand.h"

#include "SpriteBatchWrapper.h"
#include "SpriteWrapper.h"
#include "TextWrapper.h"	

RenderCommand::RenderCommand(const std::shared_ptr<SpriteWrapper>& aSprite)
{
	Init(aSprite);
}

RenderCommand::RenderCommand(const std::shared_ptr<SpriteBatchWrapper>& aSpriteBatch)
{
	Init(aSpriteBatch);
}

RenderCommand::RenderCommand(const std::shared_ptr<TextWrapper>& aText)
{
	Init(aText);
}

RenderCommand::RenderCommand(const RenderCommand& anOther)
{
	CopyFrom(anOther);
}

RenderCommand::RenderCommand(RenderCommand&& anOther) noexcept
{
	MoveFrom(std::move(anOther));
}

RenderCommand::~RenderCommand()
{
	Reset();
}

RenderCommand& RenderCommand::operator=(const RenderCommand& anOther)
{
	Reset();

	CopyFrom(anOther);

	return *this;
}

RenderCommand& RenderCommand::operator=(RenderCommand&& anOther)
{
	Reset();

	MoveFrom(std::move(anOther));

	return *this;
}

void RenderCommand::Init(const std::shared_ptr<SpriteWrapper>& aSprite)
{
	Reset();

	myType = RenderObjectType::Sprite;
	myLayer = aSprite->GetLayer();
	myPanStrengthFactor = aSprite->GetPanStrengthFactor();

	new (&mySpriteRenderData) SpriteRenderData(aSprite->myRenderData);
}

void RenderCommand::Init(const std::shared_ptr<SpriteBatchWrapper>& aSpriteBatch)
{
	Reset();

	myType = RenderObjectType::SpriteBatch;
	myLayer = aSpriteBatch->GetLayer();
	myPanStrengthFactor = aSpriteBatch->GetPanStrengthFactor();

	new (&mySpriteBatchRenderData) SpriteBatchRenderData();

	mySpriteBatchRenderData.myTexture = aSpriteBatch->myTexture;
	mySpriteBatchRenderData.mySprites.reserve(aSpriteBatch->mySprites.size());
	for (const auto& sprite : aSpriteBatch->mySprites)
	{
		mySpriteBatchRenderData.mySprites.push_back(sprite->myRenderData);
	}
}

void RenderCommand::Init(const std::shared_ptr<TextWrapper>& aText)
{
	Reset();

	myType = RenderObjectType::Text;
	myLayer = aText->GetLayer();
	myPanStrengthFactor = aText->GetPanStrengthFactor();

	new (&myText) TextRenderData();

	myText.myText = aText->GetText();
	myText.myRotation = aText->GetRotation();
	myText.myScale = aText->GetScale();
	myText.myColor = aText->GetColor();
	myText.myPosition = aText->GetPosition() + CU::Vector2<float>(aText->GetWidth() * -aText->GetPivot().x, static_cast<float>(aText->GetFontSize()) + aText->GetHeight() * -aText->GetPivot().y);

	myText.myPathAndName = aText->GetPathAndName();
	myText.myFontSize = aText->GetFontSize();
	myText.myBorderSize = aText->GetBoderSize();
}

void RenderCommand::CopyFrom(const RenderCommand& anOther)
{
	myType = anOther.myType;
	myLayer = anOther.myLayer;
	myPanStrengthFactor = anOther.myPanStrengthFactor;

	switch (anOther.myType)
	{
	case RenderObjectType::Sprite:
		new (&mySpriteRenderData) SpriteRenderData(anOther.mySpriteRenderData);

		break;

	case RenderObjectType::SpriteBatch:
		new (&mySpriteBatchRenderData) SpriteBatchRenderData(anOther.mySpriteBatchRenderData);

		break;

	case RenderObjectType::Text:
		new (&myText) TextRenderData(anOther.myText);

		break;

	default:
		assert(false);

		break;
	}
}

void RenderCommand::MoveFrom(RenderCommand&& anOther)
{
	myType = anOther.myType;
	myLayer = anOther.myLayer;
	myPanStrengthFactor = anOther.myPanStrengthFactor;

	switch (anOther.myType)
	{
	case RenderObjectType::Sprite:
		new (&mySpriteRenderData) SpriteRenderData(std::move(anOther.mySpriteRenderData));

		break;

	case RenderObjectType::SpriteBatch:
		new (&mySpriteBatchRenderData) SpriteBatchRenderData(std::move(anOther.mySpriteBatchRenderData));

		break;

	case RenderObjectType::Text:
		new (&myText) TextRenderData(std::move(anOther.myText));

		break;

	default:
		assert(false);

		break;
	}
}

void RenderCommand::Reset()
{
	// TODO: If the active render data object has a destructor we need to call it here

	switch (myType)
	{
	case RenderObjectType::Sprite:
		// NOTE: Do nothing
		break;

	case RenderObjectType::SpriteBatch:
		mySpriteBatchRenderData.~SpriteBatchRenderData();
		break;

	case RenderObjectType::Text:
		myText.~TextRenderData();
		break;
	}

	myType = RenderObjectType::Unknown;
}
