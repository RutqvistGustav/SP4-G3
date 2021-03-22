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

int TiledParser::GetWidthInTiles() const
{
	return myResult->GetWidth();
}

int TiledParser::GetHeightInTiles() const
{
	return myResult->GetHeight();
}

float TiledParser::GetWidth() const
{
	return static_cast<float>(myResult->GetWidth() * myResult->GetTileWidth());
}

float TiledParser::GetHeight() const
{
	return static_cast<float>(myResult->GetHeight() * myResult->GetTileHeight());
}

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

	tson::Layer* backgroundSolidLayer = map->getLayer("SolidBack");
	tson::Layer* solidLayer = map->getLayer("Solid");
	tson::Layer* foregroundSolidLayer = map->getLayer("SolidFront");

	tson::Layer* foregroundLayer = map->getLayer("Foreground");

	tson::Layer* entityLayer = map->getLayer("Entities");

	const std::array<std::pair<tson::Layer*, int>, 5> layers = {
		{
			{ backgroundLayer, GameLayer::Background },
			{ backgroundSolidLayer, GameLayer::BackgroundSolid },
			{ solidLayer, GameLayer::Solid },
			{ foregroundSolidLayer, GameLayer::ForegroundSolid },
			{ foregroundLayer, GameLayer::Foreground }
		}
	};

	for (const auto& layer : layers)
	{
		if (layer.first != nullptr && !ParseTileLayer(layer.first, layer.second))
		{
			ERROR_PRINT("Failed to parse layer %i in map! %s", layer.second, aMapPath.c_str());

			return false;
		}
	}

	if (entityLayer != nullptr && !ParseEntityLayer(entityLayer))
	{
		ERROR_PRINT("Failed to parse entity layer in map! %s", aMapPath.c_str());

		return false;
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

bool TiledParser::ParseTileLayer(tson::Layer* aLayer, int someOrder)
{
	assert(aLayer != nullptr);
	assert(aLayer->getType() == tson::LayerType::TileLayer);
	assert(!aLayer->getMap()->isInfinite());
	
	TiledLayer& newLayer = myResult->NewLayer(aLayer->getName(), someOrder);

	for (const auto& [id, tile] : aLayer->getTileData())
	{
		const int x = std::get<0>(id);
		const int y = std::get<1>(id);

		const std::uint32_t gid = tile->getGid();

		std::shared_ptr<TiledTile> gameTile = myTiledCache.TryFindTile(gid);

		if (gameTile == nullptr)
		{
			const std::string tilsetKey = tile->getTileset()->getImagePath().u8string();
			const auto& tilesetSize = tile->getTileset()->getImageSize();
			const auto& drawingRect = tile->getDrawingRect();

			TextureRect tileRect{};
			tileRect.myStartX = static_cast<float>(drawingRect.x) / static_cast<float>(tilesetSize.x);
			tileRect.myStartY = static_cast<float>(drawingRect.y) / static_cast<float>(tilesetSize.y);
			tileRect.myEndX = tileRect.myStartX + static_cast<float>(drawingRect.width) / static_cast<float>(tilesetSize.x);
			tileRect.myEndY = tileRect.myStartY + static_cast<float>(drawingRect.height) / static_cast<float>(tilesetSize.y);

			gameTile = std::make_shared<TiledTile>(tilsetKey, tileRect);

			for (const auto& object : tile->getObjectgroup().getObjects())
			{
				const float objectX = static_cast<float>(object.getPosition().x);
				const float objectY = static_cast<float>(object.getPosition().x);
				const float objectW = static_cast<float>(object.getSize().x);
				const float objectH = static_cast<float>(object.getSize().y);

				gameTile->AddCollisionBox({ objectX, objectY, objectW, objectH });
			}

			myTiledCache.AddTile(gid, gameTile);
		}

		newLayer.AddTile(x, y, gameTile);
	}

	return true;
}

bool TiledParser::ParseEntityLayer(tson::Layer* aLayer)
{
	assert(aLayer != nullptr);
	assert(aLayer->getType() == tson::LayerType::ObjectGroup);
	assert(!aLayer->getMap()->isInfinite());

	for (auto& object : aLayer->getObjects())
	{
		std::string type;
		std::string subType;

		const tson::Property* typeProp = object.getProp("Type");
		const tson::Property* subTypeProp = object.getProp("SubType");
		
		const std::uint32_t objectGid = object.getGid();
		if (objectGid > 0)
		{
			tson::Tileset* objectTileset = aLayer->getMap()->getTilesetByGid(objectGid);
			assert(objectTileset != nullptr);

			auto tile = objectTileset->getTile(objectGid);

			const tson::Property* tileTypeProp = tile->getProp("Type");
			const tson::Property* tileSubTypeProp = tile->getProp("SubType");

			if (typeProp == nullptr) typeProp = tileTypeProp;
			if (subTypeProp == nullptr) subTypeProp = tileSubTypeProp;
		}

		assert(typeProp != nullptr && "Entity type must be provided!");
		assert(typeProp->getType() == tson::Type::String && "Entity type must be string!");

		type = typeProp->getValue<std::string>();

		if (subTypeProp != nullptr)
		{
			assert(subTypeProp->getType() == tson::Type::String && "Entity subtype must be string!");

			subType = subTypeProp->getValue<std::string>();
		}

		myResult->AddEntity(TiledEntity(CU::Vector2<float>(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y)), type, subType));
	}

	return true;
}
