#pragma once

#include "TiledTile.h"

namespace tson
{
	class Tile;
}

class TiledMap;
class SpriteBatchWrapper;
class SpriteWrapper;

class TiledLayer
{
public:

	struct BatchInformation
	{
		std::string myBatchKey;
		std::shared_ptr<SpriteBatchWrapper> myBatch;
	};

	TiledLayer(TiledMap* aMap, const std::string& aName, int someOrder);

	void AddTile(int aPosX, int aPosY, const TiledTile& aTile);

	const TiledTile* GetTileAt(int aPosX, int aPosY) const;

	inline TiledMap* GetMap() const { return myMap; }
	inline int GetOrder() const { return myOrder; }
	inline const std::string& GetName() const { return myName; }
	inline const std::vector<BatchInformation>& GetRenderBatches() const { return myRenderBatches; }

private:

	void AddTileToBatch(int aPosX, int aPosY, const TiledTile& aTile);

	std::shared_ptr<SpriteWrapper> CreateSprite(int aPosX, int aPosY, const TiledTile& aTile) const;
	BatchInformation CreateBatchInformation(const TiledTile& aTile) const;
	void AddTileInNewBatchInformation(int aPosX, int aPosY, const TiledTile& aTile);

private:

	int myOrder;
	std::string myName;
	TiledMap* myMap;

	std::vector<std::shared_ptr<TiledTile>> myTiles;
	std::vector<BatchInformation> myRenderBatches;

};
