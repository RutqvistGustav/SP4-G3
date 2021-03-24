#pragma once

#include "Vector2.hpp"

#include <vector>

class TiledLayer;
class TiledTile;
class TiledParser;

class TiledCollision
{
public:

	TiledCollision(const TiledParser* aParser);

	const TiledTile* GetTileAt(const CU::Vector2<float>& aPosition)const;

private:

	int myTileWidth{};
	int myTileHeight{};

	std::vector<const TiledLayer*> mySolidLayers{};

	const TiledParser* myParser;

};
