#pragma once

#include "TileType.h"
#include "TextureRect.h"

class TiledTile
{
public:

	TiledTile(const std::string& aTilesetKey, const TextureRect& aTextureRect);

	inline TileType GetType() const { return myType; }
	inline const std::string& GetTilesetKey() const { return myTilesetKey; }
	inline const TextureRect& GetTextureRect() const { return myTextureRect; }

private:

	TileType myType{ TileType::None };
	
	std::string myTilesetKey;
	TextureRect myTextureRect;

};
