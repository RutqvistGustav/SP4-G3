#include "stdafx.h"
#include "TiledCollision.h"

#include "TiledTile.h"
#include "TiledParser.h"

TiledCollision::TiledCollision(const TiledParser* aParser) :
	myParser(aParser)
{
	assert(myParser != nullptr);

	myTileWidth = myParser->myResult->GetTileWidth();
	myTileHeight = myParser->myResult->GetTileWidth();

	mySolidLayer = myParser->myResult->GetLayerByName("Solid");

	assert(mySolidLayer != nullptr && "No solid layer, should always exist!");
}

const TiledTile* TiledCollision::GetTileAt(const CU::Vector2<float>& aPosition)const
{
	const int tileX = static_cast<int>(std::floorf(aPosition.x / myTileWidth));
	const int tileY = static_cast<int>(std::floorf(aPosition.y / myTileHeight));

	return mySolidLayer->GetTileAt(tileX, tileY);
}
