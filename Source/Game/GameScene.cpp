#include "stdafx.h"
#include "GameScene.h"

#include "Player.h"

#include "Metrics.h"

#include "RenderCommand.h"
#include "RenderQueue.h"

#include "SpriteWrapper.h"

#include "CollisionManager.h"
// Enemy
#include "EnemyFactory.h"
#include "Enemy.h"

#include "TiledParser.h"
#include "TiledRenderer.h"
#include "TiledCollision.h"

GameScene::GameScene() = default;
GameScene::~GameScene() = default;

void GameScene::Init()
{
	myTga2dLogoSprite = std::make_shared<SpriteWrapper>("Sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPosition(Metrics::GetReferenceSize() * 0.5f);

	myTiledParser = std::make_unique<TiledParser>("Maps/HampusTestMap.json");
	//myTiledParser = std::make_unique<TiledParser>("Maps/test_map.json");
	myTiledRenderer = std::make_unique<TiledRenderer>(myTiledParser.get());
	myTiledCollision = std::make_unique<TiledCollision>(myTiledParser.get());
	myCollisionManager = std::make_unique<CollisionManager>(myTiledCollision.get());

	for (size_t i = 0; i < 10; ++i)//temp floor
	{
		AddGameObject(std::make_shared<GameObject>(this));
		myGameObjects[i]->Init();
		myGameObjects[i]->SetPosition({ 200.0f * (i + 1) , 1080.0f});
	}

	myPlayer = std::make_unique<Player>(this);
	myPlayer->SetPosition({ 950.0f, 540.0f });
	myPlayer->Init();
}

void GameScene::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	myCollisionManager->Update();
	myPlayer->Update(aDeltaTime, anUpdateContext);
}

void GameScene::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	aRenderQueue->Queue(RenderCommand(myTga2dLogoSprite));
	myPlayer->Render(aRenderQueue, aRenderContext);
#ifdef _DEBUG
	myCollisionManager->RenderDebug();
#endif //_DEBUG

	myTiledRenderer->Render(aRenderQueue, aRenderContext);
}
