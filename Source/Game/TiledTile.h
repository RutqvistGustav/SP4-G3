#pragma once

#include "TiledCollisionBox.h"
#include "TileType.h"
#include "TextureRect.h"

class TiledTile
{
public:

	TiledTile(const std::string& aTilesetKey, const TextureRect& aTextureRect);

	inline TileType GetType() const { return myType; }
	inline const std::string& GetTilesetKey() const { return myTilesetKey; }
	inline const TextureRect& GetTextureRect() const { return myTextureRect; }

	inline const std::vector<TiledCollisionBox>& GetCollisionBoxes() const { return myCollisionBoxes; }

private:

	void AddCollisionBox(const TiledCollisionBox& aCollisionBox);

private:

	friend class TiledParser;

	TileType myType{ TileType::None };
	
	std::string myTilesetKey;
	TextureRect myTextureRect;

	std::vector<TiledCollisionBox> myCollisionBoxes;

};
