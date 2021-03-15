#pragma once

#include "Vector2.hpp"

class TiledLayer;
class TiledTile;
class TiledParser;

class TiledCollision
{
public:

	TiledCollision(const TiledParser* aParser);

	const TiledTile* GetTileAt(const CU::Vector2<float>& aPosition);

private:

	int myTileWidth{};
	int myTileHeight{};

	const TiledLayer* mySolidLayer{};

	const TiledParser* myParser;

};
