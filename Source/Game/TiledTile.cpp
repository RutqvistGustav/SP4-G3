#include "stdafx.h"
#include "TiledTile.h"

#include "TilesonImport.h"

TiledTile::TiledTile(const std::string& aTilesetKey, const TextureRect& aTextureRect) :
	myTilesetKey(aTilesetKey),
	myTextureRect(aTextureRect)
{
}
