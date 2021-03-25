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
	TextWrapper(const char* aPathAndName, Tga2D::EFontSize aFontSize, unsigned char aBorderSize);

	float GetWidth();
	float GetHeight();

	void SetColor(const Tga2D::CColor& aColor);
	Tga2D::CColor GetColor() const;

	void SetText(const std::string& aText);
	std::string GetText() const;

	void SetPosition(const CommonUtilities::Vector2<float>& aPosition);
	CommonUtilities::Vector2<float> GetPosition() const;

	void SetScale(float aScale);
	float GetScale() const;

	std::string GetPathAndName() const;

	void SetRotation(float aRotation);
	float GetRotation() const;

private:
	friend class RenderCommand;

	std::shared_ptr<Tga2D::CText> myText;
};

