#include "stdafx.h"
#include "TiledCollision.h"

#include "TiledTile.h"
#include "TiledParser.h"

TiledCollision::TiledCollision(const TiledParser* aParser) :
	myParser(aParser)
{
	assert(myParser != nullptr);

	myTileWidth = myParser->myResult->GetTileWidth();
	myTileHeight = myParser->myResult->GetTileHeight();

	mySolidLayers.reserve(3);

	const TiledLayer* solidBack = myParser->myResult->GetLayerByName("SolidBack");
	const TiledLayer* solid = myParser->myResult->GetLayerByName("Solid");
	const TiledLayer* solidFront = myParser->myResult->GetLayerByName("SolidFront");

	if (solidFront != nullptr) mySolidLayers.push_back(solidFront);
	if (solid != nullptr) mySolidLayers.push_back(solid);
	if (solidBack != nullptr) mySolidLayers.push_back(solidBack);
}

const TiledTile* TiledCollision::GetTileAt(const CU::Vector2<float>& aPosition)const
{
	const int tileX = static_cast<int>(std::floorf(aPosition.x / myTileWidth));
	const int tileY = static_cast<int>(std::floorf(aPosition.y / myTileHeight));

	// TODO: If performance is a problem and depending on what information is needed from the tiles this could be optimized by merging all layers into one
	for (std::size_t i = 0; i < mySolidLayers.size(); ++i)
	{
		const TiledTile* tile{};
		if (mySolidLayers[i] != nullptr)
		{
			tile = mySolidLayers[i]->GetTileAt(tileX, tileY);
			if (tile != nullptr)
			{
				return tile;
			}
		}
	}

	return nullptr;
}
