#include "stdafx.h"
#include "Minimap.h"

#include "DynamicTexture.h"
#include "Metrics.h"
#include "MathHelper.h"

#include "RenderCommand.h"
#include "RenderQueue.h"
#include "SpriteWrapper.h"

#include "TiledCollision.h"
#include "TiledParser.h"

// NOTE: Ideas for possible implementations:
// 1. Create a dynamic texture that will be updated and panned as necessary where each tile is a pixel,
// then render everything with 1 sprite bound to that texture.
// The texture should be as large as possible (preferrably containing the whole map) to minimize update frequency.
// For our purposes a single texture with no updates should be doable (maps will at the extreme be 512-1024 per dimension)
// 2. A sprite per pixel and then batch the whole map and update the sprites as neccessary for panning etc.

// For current needs implementation 1 is the best.

Minimap::Minimap(TiledParser* aTiledParser, TiledCollision* aTiledCollision) :
	myTiledParser(aTiledParser),
	myTiledCollision(aTiledCollision)
{
	myMapTexture = std::make_unique<DynamicTexture>(myTiledParser->GetWidthInTiles(), myTiledParser->GetHeightInTiles());

	// TODO: Change pixel sampling for better pixel look
	myMapSprite = std::make_shared<SpriteWrapper>();
	myMapSprite->SetTexture(myMapTexture->GetTexture());

	myMapSprite->SetSize(Metrics::GetReferenceSize());
	myMapSprite->SetPosition(Metrics::GetReferenceSize() * 0.5f);

	myMapSprite->SetPanStrengthFactor(0.0f);

	myMapSprite->SetLayer(GameLayer::Minimap);

	UpdateTexture();

	SetGameView(AABB({ 0.0f, 0.0f }, { 1920.0f, 1080.0f }));
	SetUIView(AABB({ 0.0f, 0.0f }, { 300.0f * myGameView.GetSize().x / myGameView.GetSize().y, 300.0f }));
}

Minimap::~Minimap() = default;

void Minimap::Update(float aDeltaTime)
{
}

void Minimap::Render(RenderQueue* const aRenderQueue)
{
	aRenderQueue->Queue(RenderCommand(myMapSprite));
}

void Minimap::SetGameView(const AABB& aGameView)
{
	myGameView = aGameView;

	UpdateView();
}

void Minimap::SetUIView(const AABB& aUIView)
{
	myUIView = aUIView;

	UpdateView();
}

void Minimap::UpdateTexture()
{
	for (int y = 0; y < myMapTexture->GetHeight(); ++y)
	{
		for (int x = 0; x < myMapTexture->GetWidth(); ++x)
		{
			// TODO: Ugly solution for the moment
			const TiledTile* tile = myTiledCollision->GetTileAt({ x * 64.0f, y * 64.0f });

			Tga2D::CColor targetColor = Tga2D::CColor(1.0f, 1.0f, 1.0f, 1.0f);

			if (tile != nullptr)
			{
				targetColor = Tga2D::CColor(0.0f, 0.0f, 0.0f, 1.0f);
			}

			myMapTexture->SetPixel(x, y, targetColor);
		}
	}

	myMapTexture->CommitChanges();
}

void Minimap::UpdateView()
{
	const CU::Vector2<float> pixelSize = myMapTexture->GetNormalizedPixelSize();

	const float maxU = pixelSize.x * myMapTexture->GetWidth();
	const float maxV = pixelSize.y * myMapTexture->GetHeight();

	const float startU = MathHelper::Clamp(pixelSize.x * myGameView.GetMin().x, 0.0f, maxU);
	const float startV = MathHelper::Clamp(pixelSize.y * myGameView.GetMin().y, 0.0f, maxV);

	const float endU = MathHelper::Clamp(pixelSize.x * myGameView.GetMax().x, 0.0f, maxU);
	const float endV = MathHelper::Clamp(pixelSize.y * myGameView.GetMax().y, 0.0f, maxV);

	myMapSprite->SetTextureRect({ startU, startV, endU, endV });
	myMapSprite->SetPosition(myUIView.GetCenter());
	myMapSprite->SetSize(myUIView.GetSize());
}
