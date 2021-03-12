#pragma once

#include "TiledLayer.h"

namespace tson
{
	class Tileset;
}

namespace Tga2D
{
	class CTexture;
}

class TiledMap
{
public:

	TiledMap(int someWidth, int someHeight, int someTileWidth, int someTileHeight);

	bool AddTileset(const tson::Tileset& aTileset);
	TiledLayer& NewLayer(const std::string& aName, int someOrder);

	Tga2D::CTexture* GetTilesetTexture(const std::string& aTilesetKey) const;

	const TiledLayer* GetLayerByName(const std::string& aName) const;
	inline const std::vector<TiledLayer>& GetLayers() const { return myLayers; }

	inline int GetWidth() const { return myWidth; }
	inline int GetHeight() const { return myHeight; }

	inline int GetTileWidth() const { return myTileWidth; }
	inline int GetTileHeight() const { return myTileHeight; }

private:

	int myWidth{};
	int myHeight{};

	int myTileWidth{};
	int myTileHeight{};

	std::unordered_map<std::string, Tga2D::CTexture*> myTilesets;
	std::vector<TiledLayer> myLayers;

};
