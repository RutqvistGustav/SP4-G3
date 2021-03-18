#include "stdafx.h"
#include "TiledCache.h"

void TiledCache::AddTile(std::uint32_t someGid, std::shared_ptr<TiledTile> aTile)
{
    myCachedTiles.insert({ someGid, aTile });
}

std::shared_ptr<TiledTile> TiledCache::TryFindTile(std::uint32_t someGid)
{
    auto it = myCachedTiles.find(someGid);
    if (it != myCachedTiles.end())
    {
        return it->second;
    }

    return nullptr;
}
