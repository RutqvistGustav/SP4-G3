#pragma once

#include "ObjectWrapper.h"
#include "SpriteRenderData.h"

#include <string>

/// <summary>
/// OBS! Always wrap in an std::shared_ptr!
/// </summary>
class SpriteWrapper : public ObjectWrapper
{
public:

	SpriteWrapper();
	SpriteWrapper(const char* aSpritePath);
	SpriteWrapper(const std::string& aSpritePath);

	void SetPosition(const CommonUtilities::Vector2<float> aPosition);
	const CommonUtilities::Vector2<float>& GetPosition() const;

	void SetPivot(const CommonUtilities::Vector2<float> aPivot);
	const CommonUtilities::Vector2<float>& GetPivot() const;

	void SetSize(const CommonUtilities::Vector2<float> aSize);
	const CommonUtilities::Vector2<float>& GetSize() const;

	void SetRotation(const float aRotation);
	float GetRotation() const;

	void SetColor(const Tga2D::CColor& aColor);
	const Tga2D::CColor& GetColor() const;

	void SetTexture(const std::string& aSpritePath);
	void SetTexture(Tga2D::CTexture* aTexture);
	const Tga2D::CTexture* GetTexture() const;

	void SetTextureRect(const TextureRect& aTextureRect);
	const TextureRect& GetTextureRect() const;

private:

	friend class RenderCommand;

	SpriteRenderData myRenderData;

};
