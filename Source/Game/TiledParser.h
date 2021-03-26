#pragma once

#include "TiledMap.h"
#include "TiledCache.h"

#include <unordered_map>
#include <string>

namespace tson
{
	class Layer;
	class Map;
}

namespace Tga2D
{
	class CTexture;
}

class SpriteBatchWrapper;

class TiledParser
{
public:

	TiledParser(const std::string& aMapPath);
	~TiledParser();

	int GetWidthInTiles() const;
	int GetHeightInTiles() const;

	float GetWidth() const;
	float GetHeight() const;

private:

	friend class TiledCollision;
	friend class TiledRenderer;
	friend class TiledEntities;
	friend class Minimap;
	
	bool Load(const std::string& aMapPath);

	bool ParseTileset(tson::Map* aMap);
	bool ParseTileLayer(tson::Layer* aLayer, int someOrder);
	bool ParseEntityLayer(tson::Layer* aLayer);

private:

	std::unique_ptr<TiledMap> myResult;
	TiledCache myTiledCache;

};
