#include "stdafx.h"
#include "TiledTile.h"

TiledTile::TiledTile(const std::string& aTilesetKey, const TextureRect& aTextureRect) :
	myTilesetKey(aTilesetKey),
	myTextureRect(aTextureRect)
{}
