#pragma once

#include "ObjectWrapper.h"
#include "SpriteRenderData.h"
#include "SpriteWrapper.h"

#include <vector>

namespace Tga2D
{
	class CTexture;
}

/// <summary>
/// OBS! Always wrap in an std::shared_ptr!
/// </summary>
class SpriteBatchWrapper : public ObjectWrapper
{
public:

	static constexpr int ourMaxSpriteCount = 2048;

	SpriteBatchWrapper(Tga2D::CTexture* aTexture);
	SpriteBatchWrapper(const char* aSpritePath);
	SpriteBatchWrapper(const std::string& aSpritePath);

	bool Add(const std::shared_ptr<SpriteWrapper>& aSprite);
	bool Remove(const std::shared_ptr<SpriteWrapper>& aSprite);

	void Clear();

	Tga2D::CTexture* GetTexture();

	bool IsFull() const;

private:

	friend class RenderCommand;

	Tga2D::CTexture* myTexture{};

	// NOTE: Could use different data structure if needed
	std::vector<std::shared_ptr<SpriteWrapper>> mySprites;

};
