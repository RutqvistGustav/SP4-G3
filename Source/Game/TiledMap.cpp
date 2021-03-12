#include "stdafx.h"
#include "TiledMap.h"

TiledMap::TiledMap(int someWidth, int someHeight, int someTileWidth, int someTileHeight) :
	myWidth(someWidth),
	myHeight(someHeight),
	myTileWidth(someTileWidth),
	myTileHeight(someTileHeight)
{}

void TiledMap::AddTileset(const std::string& aTilesetKey, Tga2D::CTexture* aTexture)
{
	myTilesets.insert({ aTilesetKey, aTexture });
}

TiledLayer& TiledMap::NewLayer(const std::string& aName, int someOrder)
{
	return myLayers.emplace_back(this, aName, someOrder);
}

Tga2D::CTexture* TiledMap::GetTilesetTexture(const std::string& aTilesetKey) const
{
	return myTilesets.at(aTilesetKey);
}

const TiledLayer* TiledMap::GetLayerByName(const std::string& aName) const
{
	// NOTE: O(n), but max amount of layers is always < 6
	auto it = std::find_if(myLayers.begin(), myLayers.end(), [aName](const TiledLayer& aLayer) { return aLayer.GetName() == aName; });
	if (it != myLayers.end())
	{
		return &(*it);
	}

	return nullptr;
}
