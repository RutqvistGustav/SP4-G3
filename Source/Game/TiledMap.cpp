#include "stdafx.h"
#include "TiledMap.h"

#include "TilesonImport.h"

#include <tga2d/texture/texture_manager.h>

static const fs::path locBasePath = "Maps";

TiledMap::TiledMap(int someWidth, int someHeight, int someTileWidth, int someTileHeight) :
	myWidth(someWidth),
	myHeight(someHeight),
	myTileWidth(someTileWidth),
	myTileHeight(someTileHeight)
{}

bool TiledMap::AddTileset(const tson::Tileset & aTileset)
{
	fs::path imagePath = locBasePath / aTileset.getImagePath();
	imagePath.replace_extension(".dds");

	const std::string finalImagePath = imagePath.u8string();

	Tga2D::CTexture* tilesetTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture(finalImagePath.c_str());

	if (tilesetTexture == nullptr || tilesetTexture->myIsFailedTexture)
	{
		ERROR_PRINT("Failed loading texture from tileset! %s", finalImagePath.c_str());

		return false;
	}

	myTilesets.insert({ aTileset.getImagePath().u8string(), tilesetTexture });

	return true;
}

TiledLayer& TiledMap::NewLayer(int someOrder)
{
	myLayers.emplace_back(this, someOrder);

	return myLayers.back();
}

Tga2D::CTexture* TiledMap::GetTilesetTexture(const std::string& aTilesetKey) const
{
	return myTilesets.at(aTilesetKey);
}
