#include "stdafx.h"
#include "TiledTile.h"

TiledTile::TiledTile(const std::string& aTilesetKey, const TextureRect& aTextureRect) :
	myTilesetKey(aTilesetKey),
	myTextureRect(aTextureRect)
{}

void TiledTile::AddCollisionBox(const TiledCollisionBox & aCollisionBox)
{
	myCollisionBoxes.push_back(aCollisionBox);
}
