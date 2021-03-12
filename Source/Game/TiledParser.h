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

	friend class TiledRenderer;
	
	bool Load(const std::string& aMapPath);

	bool ParseTileset(tson::Map* aMap);
	bool ParseLayer(tson::Layer* aLayer, int someOrder);

private:

	std::unique_ptr<TiledMap> myResult;

};
