#include "stdafx.h"
#include "SpriteBatchWrapper.h"

#include <tga2d/texture/texture_manager.h>

SpriteBatchWrapper::SpriteBatchWrapper(Tga2D::CTexture* aTexture) :
    myTexture(aTexture)
{}

SpriteBatchWrapper::SpriteBatchWrapper(const char* aSpritePath)
{
    myTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture(aSpritePath);
}

SpriteBatchWrapper::SpriteBatchWrapper(const std::string& aSpritePath) :
    SpriteBatchWrapper(aSpritePath.c_str())
{}

bool SpriteBatchWrapper::Add(const std::shared_ptr<SpriteWrapper>& aSprite)
{
    assert(!IsFull());

    mySprites.push_back(aSprite);

    return true;
}

bool SpriteBatchWrapper::Remove(const std::shared_ptr<SpriteWrapper>& aSprite)
{
    auto it = std::find(mySprites.begin(), mySprites.end(), aSprite);

    if (it != mySprites.end())
    {
        mySprites.erase(it);

        return true;
    }

    return false;
}

void SpriteBatchWrapper::Clear()
{
    mySprites.clear();
}

Tga2D::CTexture* SpriteBatchWrapper::GetTexture()
{
    return myTexture;
}

bool SpriteBatchWrapper::IsFull() const
{
    return static_cast<int>(mySprites.size()) >= SpriteBatchWrapper::ourMaxSpriteCount;
}
