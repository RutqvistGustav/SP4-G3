#include "stdafx.h"
#include "ForegroundImage.h"
#include "SpriteWrapper.h"
#include "RenderCommand.h"

ForegroundImage::ForegroundImage(float aSpeed, CU::Vector2<float> aPos, const char* aSpritePath,
	bool aMoveLeft, bool aMoveUp) :
	mySpeed(aSpeed), myPosition(aPos), myMoveLeft(aMoveLeft), myMoveUp(aMoveUp)
{
	mySprite = std::make_shared<SpriteWrapper>(aSpritePath);
	mySprite->SetPosition(myPosition);
}

void ForegroundImage::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	RenderCommand renderCommand = RenderCommand(mySprite);
	aRenderQueue->Queue(renderCommand);
}

float ForegroundImage::GetSpeed() const
{
	return mySpeed;
}

void ForegroundImage::SetSpeed(float aSpeed)
{
	mySpeed = aSpeed;
}

CU::Vector2<float> ForegroundImage::GetPosition() const
{
	return myPosition;
}

void ForegroundImage::SetPosition(CU::Vector2<float> aPos)
{
	myPosition = aPos;
	mySprite->SetPosition(myPosition);
}

bool ForegroundImage::GetMoveLeft()
{
	return myMoveLeft;
}

bool ForegroundImage::GetMoveUp()
{
	return myMoveUp;
}

void ForegroundImage::SetMoveLeft(bool aBool)
{
	myMoveLeft = aBool;
}

void ForegroundImage::SetMoveUp(bool aBool)
{
	myMoveUp = aBool;
}
