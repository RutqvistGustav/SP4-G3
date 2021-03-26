#include "stdafx.h"
#include "TextWrapper.h"
#include <tga2d/text/text.h>

TextWrapper::TextWrapper(const char* aPathAndName, Tga2D::EFontSize aFontSize, unsigned char aBorderSize) :
	myFontSize(aFontSize),
	myBorderSize(aBorderSize)
{
	myText = std::make_shared<Tga2D::CText>(aPathAndName, aFontSize, aBorderSize);
}

float TextWrapper::GetWidth()
{
	return myText->GetWidth() * Tga2D::CEngine::GetInstance()->GetWindowSize().x;
}

float TextWrapper::GetHeight()
{
	return myText->GetHeight() * Tga2D::CEngine::GetInstance()->GetWindowSize().y;
}

void TextWrapper::SetColor(const Tga2D::CColor& aColor)
{
	myText->SetColor(aColor);
}

Tga2D::CColor TextWrapper::GetColor() const
{
	return myText->GetColor();
}

void TextWrapper::SetText(const std::string& aText)
{
	myText->SetText(aText);
}

std::string TextWrapper::GetText() const
{
	return myText->GetText();
}

void TextWrapper::SetPosition(const CommonUtilities::Vector2<float>& aPosition)
{
	myText->SetPosition({ aPosition.x, aPosition.y });
}

CommonUtilities::Vector2<float> TextWrapper::GetPosition() const
{
	CommonUtilities::Vector2<float> position;
	position.x = myText->GetPosition().myX;
	position.y = myText->GetPosition().myY;
	return position;
}

void TextWrapper::SetPivot(const CU::Vector2<float>& aPivot)
{
	myPivot = aPivot;
}

const CU::Vector2<float>& TextWrapper::GetPivot() const
{
	return myPivot;
}

void TextWrapper::SetScale(float aScale)
{
	myText->SetScale(aScale);
}

float TextWrapper::GetScale() const
{
	return myText->GetScale();
}

std::string TextWrapper::GetPathAndName() const
{
	return myText->GetPathAndName();
}

Tga2D::EFontSize TextWrapper::GetFontSize() const
{
	return myFontSize;
}

unsigned char TextWrapper::GetBoderSize() const
{
	return myBorderSize;
}

void TextWrapper::SetRotation(float aRotation)
{
	myText->SetRotation(aRotation);
}

float TextWrapper::GetRotation() const
{
	return myText->GetRotation();
}
