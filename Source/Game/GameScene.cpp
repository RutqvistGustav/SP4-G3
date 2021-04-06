#include "stdafx.h"
#include "GameScene.h"

#include "Player.h"

#include "Metrics.h"

#include "RenderCommand.h"
#include "RenderQueue.h"
#include "UpdateContext.h"

#include "Camera.h"

#include "SpriteWrapper.h"
#include "DialogueBox.h"
#include "PauseMenu.h"

//Managers
#include "CollisionManager.h"
#include "EnemyManager.h"

#include "TiledParser.h"
#include "TiledRenderer.h"
#include "TiledCollision.h"
#include "TiledEntities.h"

#include "Minimap.h"

#include "GlobalServiceProvider.h"
#include "GameMessenger.h"
#include "CheckpointMessage.h"
#include "CheckpointContext.h"
#include "CollectibleManager.h"

#include "ParallaxContainer.h"

GameScene::GameScene(const std::string& aMapPath) :
	myMapPath(aMapPath)
{}

GameScene::~GameScene() = default;

void GameScene::Init()
{
	// TODO: Load different file based on which level we are on
	myTiledParser = std::make_unique<TiledParser>(myMapPath);
	//myTiledParser = std::make_unique<TiledParser>("Maps/test_map.json");
	myTiledRenderer = std::make_unique<TiledRenderer>(myTiledParser.get());
	myTiledCollision = std::make_unique<TiledCollision>(myTiledParser.get());
	myCollisionManager = std::make_unique<CollisionManager>(myTiledCollision.get());
	myTiledEntities = std::make_unique<TiledEntities>(myTiledParser.get(), this);

	myMinimap = std::make_unique<Minimap>(this, myTiledParser.get(), myTiledCollision.get());
	myParallaxContainer = std::make_unique<ParallaxContainer>(this);

	// TODO: Read from json?
	myParallaxContainer->AddLayer(0.8f, GameLayer::ParallaxForeground, "Sprites/parallax/dust_bot.dds");
	myParallaxContainer->AddLayer(0.8f, GameLayer::ParallaxForeground, "Sprites/parallax/dust_top.dds");

	myCollisionManager->IgnoreCollision(CollisionLayer::MapSolid, CollisionLayer::Default);
	myCollisionManager->IgnoreCollision(CollisionLayer::MapSolid, CollisionLayer::HUD);

	myPlayer = std::make_shared<Player>(this);
	myPlayer->Init();

	myEnemyManager = std::make_unique<EnemyManager>(this, myMinimap.get());
	myCollectibleManager = std::make_unique<CollectibleManager>(this);

	myMinimap->AddObject(myPlayer.get(), Minimap::MapObjectType::Player);

	myPauseMenu = std::make_unique<PauseMenu>();
	myPauseMenu->OnEnter(GetSceneManagerProxy(), GetLevelManagerProxy(), GetGlobalServiceProvider());
	myPauseMenu->Init();

	GetCamera()->SetLevelBounds(AABB(CU::Vector2<float>(), CU::Vector2<float>(myTiledParser->GetWidth(), myTiledParser->GetHeight())));
	GetCamera()->SetPosition(CU::Vector2<float>());

	myTiledEntities->SpawnEntities();

	const TiledEntity* playerSpawn = myTiledEntities->FindEntityWithType("PlayerSpawn");
	if (playerSpawn != nullptr)
	{
		myPlayer->SetPosition(playerSpawn->GetPosition());
		GetCamera()->SetPosition(playerSpawn->GetPosition());
		myParallaxContainer->SetParallaxOrigin(GetCamera()->GetPosition());
	}
}

void GameScene::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	if (myPauseMenu->IsGamePaused() == false)
	{
		Scene::Update(aDeltaTime, anUpdateContext);
		myPlayer->Update(aDeltaTime, anUpdateContext);

		myMinimap->SetGameView(GetCamera()->GetViewBounds());

		//Removal of marked GameObjects
		myEnemyManager->DeleteMarkedEnemies();
		myCollectibleManager->DeleteMarkedCollectables();

		//temp
		myEnemyManager->AddTargetToAllEnemies(myPlayer);
	}
	Scene::RemoveMarkedObjects();
	myCollisionManager->Update();

	myPauseMenu->Update(aDeltaTime, anUpdateContext);

	myParallaxContainer->Update(aDeltaTime);
}

void GameScene::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	Scene::Render(aRenderQueue, aRenderContext);

	myPlayer->Render(aRenderQueue, aRenderContext);
	myTiledRenderer->Render(aRenderQueue, aRenderContext);

	myParallaxContainer->Render(aRenderQueue);
	myMinimap->Render(aRenderQueue);

	myPauseMenu->Render(aRenderQueue, aRenderContext);

#ifdef _DEBUG
	myCollisionManager->RenderDebug(aRenderQueue, aRenderContext);
#endif //_DEBUG
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
