#include "stdafx.h"
#include "GameScene.h"

#include "Player.h"

#include "Metrics.h"

#include "RenderCommand.h"
#include "RenderQueue.h"

#include "Camera.h"

#include "SpriteWrapper.h"

#include "CollisionManager.h"
// Enemy
#include "EnemyFactory.h"
#include "Enemy.h"

#include "TiledParser.h"
#include "TiledRenderer.h"
#include "TiledCollision.h"

#include "GlobalServiceProvider.h"
#include "GameMessenger.h"
#include "CheckpointMessage.h"
#include "CheckpointContext.h"

GameScene::GameScene() = default;
GameScene::~GameScene() = default;

void GameScene::Init()
{
	myTga2dLogoSprite = std::make_shared<SpriteWrapper>("Sprites/tga_logo.dds");

	myPlayer = std::make_unique<Player>(this);
	myPlayer->Init();

	for (size_t i = 0; i < 10; ++i)
	{
		AddGameObject(std::make_shared<GameObject>(this));
		myGameObjects[i]->Init();
		myGameObjects[i]->SetPosition({ 190.0f * (i + 1) , 1080.0f});
	}
	
	// TODO: Load different file based on which level we are on
	myTiledParser = std::make_unique<TiledParser>("Maps/test_map.json");
	myTiledRenderer = std::make_unique<TiledRenderer>(myTiledParser.get());
	myTiledCollision = std::make_unique<TiledCollision>(myTiledParser.get());

	GetCamera()->SetLevelBounds(AABB(CU::Vector2<float>(), CU::Vector2<float>(myTiledParser->GetWidth(), myTiledParser->GetHeight())));
	GetCamera()->SetPosition(CU::Vector2<float>());
}

void GameScene::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	CollisionManager::GetInstance()->Update();
	myPlayer->Update(aDeltaTime, anUpdateContext);
}

void GameScene::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	aRenderQueue->Queue(RenderCommand(myTga2dLogoSprite));
	myPlayer->Render(aRenderQueue, aRenderContext);
#ifdef _DEBUG
	CollisionManager::GetInstance()->RenderDebug();
#endif //_DEBUG

	myTiledRenderer->Render(aRenderQueue, aRenderContext);
}

CheckpointContext GameScene::SaveCheckpoint()
{
	CheckpointContext checkpointContext;

	CheckpointMessageData checkpointMessageData{};
	checkpointMessageData.myCheckpointContext = &checkpointContext;

	GetGlobalServiceProvider()->GetGameMessenger()->Send(GameMessage::CheckpointSave, &checkpointMessageData);

	return checkpointContext;
}

void GameScene::LoadCheckpoint(CheckpointContext& aCheckpointContext)
{
	CheckpointMessageData checkpointMessageData{};
	checkpointMessageData.myCheckpointContext = &aCheckpointContext;

	GetGlobalServiceProvider()->GetGameMessenger()->Send(GameMessage::CheckpointLoad, &checkpointMessageData);
}
