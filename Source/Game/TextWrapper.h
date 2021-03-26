#pragma once
#include <string>
#include <memory>
#include "Vector2.hpp"
#include "ObjectWrapper.h"
#include <tga2d/text/text.h>

class Tga2D::CText;

class TextWrapper : public ObjectWrapper
{
public:
	TextWrapper(const char* aPathAndName, Tga2D::EFontSize aFontSize = Tga2D::EFontSize::EFontSize_14, unsigned char aBorderSize = 0);

	float GetWidth();
	float GetHeight();

	void SetColor(const Tga2D::CColor& aColor);
	Tga2D::CColor GetColor() const;

	void SetText(const std::string& aText);
	std::string GetText() const;

	void SetPosition(const CommonUtilities::Vector2<float>& aPosition);
	CommonUtilities::Vector2<float> GetPosition() const;

	void SetPivot(const CU::Vector2<float>& aPivot);
	const CU::Vector2<float>& GetPivot() const;

	void SetScale(float aScale);
	float GetScale() const;

	void SetRotation(float aRotation);
	float GetRotation() const;

	std::string GetPathAndName() const;
	Tga2D::EFontSize GetFontSize() const;
	unsigned char GetBoderSize() const;

private:
	friend class RenderCommand;

	std::shared_ptr<Tga2D::CText> myText;
	
	CU::Vector2<float> myPivot{ 0.5f, 0.5f };

	Tga2D::EFontSize myFontSize;
	unsigned char myBorderSize;
};

