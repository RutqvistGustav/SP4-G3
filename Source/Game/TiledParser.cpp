#include "stdafx.h"
#include "TiledParser.h"

#include "TilesonImport.h"

#include "GameLayer.h"

#include <tga2d/texture/texture_manager.h>

#include <cassert>

static const fs::path locBasePath = "Maps";

static const fs::path locTilesetPath = "Tilesets";
static const fs::path locObjectTypesPath = "Data/ObjectTypes.json";

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

	ParseGlobalData();

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

bool TiledParser::ParseGlobalData()
{
	std::ifstream inputStream{ locBasePath / locObjectTypesPath };

	if (!inputStream.is_open())
	{
		ERROR_PRINT("No object types file found at %s!", (locBasePath / locObjectTypesPath).u8string().c_str());

		return false;
	}

	nlohmann::json objectTypes = nlohmann::json::parse(inputStream);
	
	for (const auto& objectType : objectTypes)
	{
		std::unordered_map<std::string, std::string> properties;

		for (const auto& property : objectType["properties"])
		{
			const std::string name = property["name"];
			const std::string type = property["type"];
			const std::string value = property["value"];

			assert(type == "string" && "property type must be string!");

			properties[name] = value;
		}

		myGlobalTypeProperties.insert({ objectType["name"].get<std::string>(), properties });
	}

	return true;
}

bool TiledParser::ParseTileset(tson::Map* aMap)
{
	const std::vector<tson::Tileset>& tilesets = aMap->getTilesets();

	for (const tson::Tileset& tileset : tilesets)
	{
		fs::path imagePath = locBasePath / locTilesetPath / tileset.getImagePath();
		imagePath.replace_extension(".dds");

		const std::string finalImagePath = imagePath.u8string();

		Tga2D::CTexture* tilesetTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture(finalImagePath.c_str());

		if (tilesetTexture == nullptr || tilesetTexture->myIsFailedTexture)
		{
			// NOTE: TODO: Code to support old placement of texture files, when not used anymore this can be changed to fail immediately!

			ERROR_PRINT("Could not load tileset from intended folder, trying old folder! %s", finalImagePath.c_str());

			fs::path oldImagePath = locBasePath / tileset.getImagePath();
			oldImagePath.replace_extension(".dds");

			tilesetTexture = Tga2D::CEngine::GetInstance()->GetTextureManager().GetTexture(oldImagePath.u8string().c_str());

			if (tilesetTexture == nullptr || tilesetTexture->myIsFailedTexture)
			{
				ERROR_PRINT("Could not load tileset from old folder either! %s", oldImagePath.u8string().c_str());

				return false;
			}

			ERROR_PRINT("Tileset loaded from old folder, should be moved to new folder!");
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
		std::unordered_map<std::string, std::string> properties;
		
		auto globalTypeIt = myGlobalTypeProperties.find(object.getType());
		if (globalTypeIt != myGlobalTypeProperties.end())
		{
			for (const std::pair<std::string, std::string>& property : globalTypeIt->second)
			{
				properties[property.first] = property.second;
			}
		}

		const std::uint32_t objectGid = object.getGid();
		if (objectGid > 0)
		{
			tson::Tileset* objectTileset = aLayer->getMap()->getTilesetByGid(objectGid);
			assert(objectTileset != nullptr);

			tson::Tile* tile = objectTileset->getTile(objectGid);

			const std::map<std::string, tson::Property>& tileProperties = tile->getProperties().getProperties();

			for (const std::pair<std::string, tson::Property>& property : tileProperties)
			{
				properties[property.first] = property.second.getValue<std::string>();
			}
		}

		const std::map<std::string, tson::Property>& objectProperties = object.getProperties().getProperties();
		for (const std::pair<std::string, tson::Property>& property : objectProperties)
		{
			properties[property.first] = property.second.getValue<std::string>();
		}

		assert(properties.find("Type") != properties.end() && "Entity must have 'Type' property!");

		myResult->AddEntity(TiledEntity(CU::Vector2<float>(static_cast<float>(object.getPosition().x), static_cast<float>(object.getPosition().y)), properties));
	}

	return true;
}
