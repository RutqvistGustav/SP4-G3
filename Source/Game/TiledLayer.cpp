#include "stdafx.h"
#include "TiledLayer.h"

#include "TiledMap.h"

#include "SpriteBatchWrapper.h"
#include "SpriteWrapper.h"

TiledLayer::TiledLayer(TiledMap* aMap, int someOrder) :
	myMap(aMap),
	myOrder(someOrder)
{
	myTiles.resize(aMap->GetWidth() * aMap->GetHeight());
}

void TiledLayer::AddTile(int aPosX, int aPosY, const TiledTile& aTile)
{
	const int tileIndex = aPosX + aPosY * myMap->GetWidth();

	myTiles[tileIndex] = std::make_shared<TiledTile>(aTile);

	AddTileToBatch(aPosX, aPosY, aTile);
}

void TiledLayer::AddTileToBatch(int aPosX, int aPosY, const TiledTile& aTile)
{
	// NOTE: myRenderBatches is a vector so worst case is O(n) when searching for correct batch,
	// but we expect an average amount of batches per layer to be close to 1 so it should be fast.

	for (const auto& batchInfo : myRenderBatches)
	{
		if (batchInfo.myBatchKey == aTile.GetTilesetKey() && !batchInfo.myBatch->IsFull())
		{
			batchInfo.myBatch->Add(CreateSprite(aPosX, aPosY, aTile));
			return;
		}
	}

	AddTileInNewBatchInformation(aPosX, aPosY, aTile);
}

std::shared_ptr<SpriteWrapper> TiledLayer::CreateSprite(int aPosX, int aPosY, const TiledTile& aTile) const
{
	std::shared_ptr<SpriteWrapper> sprite = std::make_shared<SpriteWrapper>();

	sprite->SetPivot({ 0.0f, 0.0f });
	sprite->SetSize({ static_cast<float>(myMap->GetTileWidth()), static_cast<float>(myMap->GetTileHeight()) });
	sprite->SetPosition({ static_cast<float>(aPosX * myMap->GetTileWidth()), static_cast<float>(aPosY * myMap->GetTileHeight()) });
	sprite->SetTextureRect(aTile.GetTextureRect());

	return sprite;
}

TiledLayer::BatchInformation TiledLayer::CreateBatchInformation(const TiledTile& aTile) const
{
	Tga2D::CTexture* tileTexture = myMap->GetTilesetTexture(aTile.GetTilesetKey());
	assert(tileTexture != nullptr);

	TiledLayer::BatchInformation batchInfo;
	batchInfo.myBatchKey = aTile.GetTilesetKey();
	batchInfo.myBatch = std::make_shared<SpriteBatchWrapper>(tileTexture);
	batchInfo.myBatch->SetLayer(myOrder);

	return batchInfo;
}

void TiledLayer::AddTileInNewBatchInformation(int aPosX, int aPosY, const TiledTile& aTile)
{
	BatchInformation batchInfo = CreateBatchInformation(aTile);

	batchInfo.myBatch->Add(CreateSprite(aPosX, aPosY, aTile));

	myRenderBatches.push_back(batchInfo);
}
