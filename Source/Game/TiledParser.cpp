#include "stdafx.h"
#include "TiledParser.h"

#include "TilesonImport.h"

#include "GameLayer.h"

#include <tga2d/texture/texture_manager.h>

#include <cassert>

static const fs::path locBasePath = "Maps";

TiledParser::TiledParser(const std::string& aMapPath)
{
	Load(aMapPath);
}

TiledParser::~TiledParser() = default;

bool TiledParser::Load(const std::string& aMapPath)
{
	tson::Tileson tileson;
	std::unique_ptr<tson::Map> map = tileson.parse(aMapPath);

	if (map->getStatus() != tson::ParseStatus::OK)
	{
		ERROR_PRINT("Could not parse tileson map! %s", aMapPath.c_str());

		return false;
	}

	myResult = std::make_unique<TiledMap>(map->getSize().x, map->getSize().y, map->getTileSize().x, map->getTileSize().y);

	if (!ParseTileset(map.get()))
	{
		ERROR_PRINT("Could not parse tileset in map! %s", aMapPath.c_str());

		return false;
	}

	tson::Layer* backgroundLayer = map->getLayer("Background");
	tson::Layer* solidLayer = map->getLayer("Solid");
	tson::Layer* foregroundLayer = map->getLayer("Foreground");

	const std::array<std::pair<tson::Layer*, int>, 3> layers = {
		{
			{ backgroundLayer, GameLayer::Background },
			{ solidLayer, GameLayer::Solid },
			{ foregroundLayer, GameLayer::Foreground }
		}
	};

	for (const auto& layer : layers)
	{
		if (layer.first != nullptr && !ParseLayer(layer.first, layer.second))
		{
			ERROR_PRINT("Failed to parse layer %i in map! %s", layer.second, aMapPath.c_str());

			return false;
		}
	}

	return true;
}

bool TiledParser::ParseTileset(tson::Map* aMap)
{
	const std::vector<tson::Tileset>& tilesets = aMap->getTilesets();

	for (const tson::Tileset& tileset : tilesets)
	{
		fs::path imagePath = locBasePath / tileset.getImagePath();
		imagePath.replace_extension(".dds");

		const std::string finalImagePath = imagePath.u8string();

		Tga2D::CTexture* tilesetTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture(finalImagePath.c_str());

		if (tilesetTexture == nullptr || tilesetTexture->myIsFailedTexture)
		{
			ERROR_PRINT("Failed loading texture from tileset! %s", finalImagePath.c_str());

			return false;
		}

		myResult->AddTileset(tileset.getImagePath().u8string(), tilesetTexture);
	}

	return true;
}

bool TiledParser::ParseLayer(tson::Layer* aLayer, int someOrder)
{
	assert(aLayer != nullptr);
	assert(aLayer->getType() == tson::LayerType::TileLayer); // TODO?: NOTE: Only support tile layers for now
	assert(!aLayer->getMap()->isInfinite());
	
	TiledLayer& newLayer = myResult->NewLayer(aLayer->getName(), someOrder);

	for (const auto& [id, tile] : aLayer->getTileData())
	{
		const int x = std::get<0>(id);
		const int y = std::get<1>(id);

		const std::string tilsetKey = tile->getTileset()->getImagePath().u8string();
		const auto& tilesetSize = tile->getTileset()->getImageSize();
		const auto& drawingRect = tile->getDrawingRect();

		TextureRect tileRect{};
		tileRect.myStartX = static_cast<float>(drawingRect.x) / static_cast<float>(tilesetSize.x);
		tileRect.myStartY = static_cast<float>(drawingRect.y) / static_cast<float>(tilesetSize.y);
		tileRect.myEndX = tileRect.myStartX + static_cast<float>(drawingRect.width) / static_cast<float>(tilesetSize.x);
		tileRect.myEndY = tileRect.myStartY + static_cast<float>(drawingRect.height) / static_cast<float>(tilesetSize.y);

		TiledTile newTile{ tilsetKey, tileRect };

		newLayer.AddTile(x, y, newTile);
	}

	return true;
}
