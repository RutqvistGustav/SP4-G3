#pragma once

#include "TiledLayer.h"
#include "TiledEntity.h"

namespace Tga2D
{
	class CTexture;
}

class TiledMap
{
public:

	TiledMap(int someWidth, int someHeight, int someTileWidth, int someTileHeight);

	void AddEntity(const TiledEntity& anEntity);
	void AddTileset(const std::string& aTilesetKey, Tga2D::CTexture* aTexture);
	TiledLayer& NewLayer(const std::string& aName, int someOrder);

	Tga2D::CTexture* GetTilesetTexture(const std::string& aTilesetKey) const;

	inline const std::vector<TiledEntity>& GetEntities() const { return myEntities; }

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

	std::vector<TiledEntity> myEntities;

	std::unordered_map<std::string, Tga2D::CTexture*> myTilesets;
	std::vector<TiledLayer> myLayers;

};
