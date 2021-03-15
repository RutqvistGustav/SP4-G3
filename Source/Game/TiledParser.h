#pragma once

#include "TiledMap.h"

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

private:

	friend class TiledCollision;
	friend class TiledRenderer;
	
	bool Load(const std::string& aMapPath);

	bool ParseTileset(tson::Map* aMap);
	bool ParseTileLayer(tson::Layer* aLayer, int someOrder);
	bool ParseEntityLayer(tson::Layer* aLayer);

private:

	std::unique_ptr<TiledMap> myResult;

};