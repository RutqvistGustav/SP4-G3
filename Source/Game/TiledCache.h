#pragma once

#include <unordered_map>

class TiledTile;

class TiledCache
{
public:

	void AddTile(std::uint32_t someGid, std::shared_ptr<TiledTile> aTile);
	std::shared_ptr<TiledTile> TryFindTile(std::uint32_t someGid);

private:

	std::unordered_map<std::uint32_t, std::shared_ptr<TiledTile>> myCachedTiles;

};
