#include "stdafx.h"
#include "SpriteWrapper.h"

#include <tga2d/texture/texture_manager.h>

SpriteWrapper::SpriteWrapper()
{
	SetTexture("");
}

SpriteWrapper::SpriteWrapper(const char* aSpritePath)
{
	SetTexture(aSpritePath != nullptr ? std::string(aSpritePath) : "");
}

SpriteWrapper::SpriteWrapper(const std::string& aSpritePath)
{
	SetTexture(aSpritePath);
}

void SpriteWrapper::SetPosition(const CommonUtilities::Vector2<float> aPosition)
{
	myRenderData.myPosition = aPosition;
}

const CommonUtilities::Vector2<float>& SpriteWrapper::GetPosition() const
{
	return myRenderData.myPosition;
}

void SpriteWrapper::SetPivot(const CommonUtilities::Vector2<float> aPivot)
{
	myRenderData.myPivot = aPivot;
}

const CommonUtilities::Vector2<float>& SpriteWrapper::GetPivot() const
{
	return myRenderData.myPivot;
}

void SpriteWrapper::SetSize(const CommonUtilities::Vector2<float> aSize)
{
	myRenderData.mySize = aSize;
}

const CommonUtilities::Vector2<float>& SpriteWrapper::GetSize() const
{
	return myRenderData.mySize;
}

void SpriteWrapper::SetRotation(const float aRotation)
{
	myRenderData.myRotation = aRotation;
}

float SpriteWrapper::GetRotation() const
{
	return myRenderData.myRotation;
}

void SpriteWrapper::SetColor(const Tga2D::CColor& aColor)
{
	myRenderData.myColor = aColor;
}

const Tga2D::CColor& SpriteWrapper::GetColor() const
{
	return myRenderData.myColor;
}

void SpriteWrapper::SetTexture(const std::string& aSpritePath)
{
	if (aSpritePath.empty())
	{
		myRenderData.myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetWhiteSquareTexture();
	}
	else
	{
		myRenderData.myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture(aSpritePath.c_str());
	}
	
	assert(!myRenderData.myTexture->myIsFailedTexture);

	VECTOR2UI imageSize = myRenderData.myTexture->myImageSize;

	SetSize({ static_cast<float>(imageSize.myX), static_cast<float>(imageSize.myY) });
}

void SpriteWrapper::SetTextureRect(const TextureRect& aTextureRect)
{
	myRenderData.myTextureRect = aTextureRect;
}

const TextureRect& SpriteWrapper::GetTextureRect() const
{
	return myRenderData.myTextureRect;
}
