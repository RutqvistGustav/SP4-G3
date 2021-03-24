#pragma once

#include "Vector2.hpp"

#include <array>

class TiledLayer;
class TiledTile;
class TiledParser;

class TiledCollision
{
public:

	TiledCollision(const TiledParser* aParser);

	const TiledTile* GetTileAt(const CU::Vector2<float>& aPosition)const;

	// inline const TiledLayer* GetLayer()const { return mySolidLayer; }

private:

	int myTileWidth{};
	int myTileHeight{};

	std::array<const TiledLayer*, 3> mySolidLayers{};

	const TiledParser* myParser;

};
