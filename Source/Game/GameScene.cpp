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
#include "Foreground.h"


GameScene::GameScene(const char* aMapPath)
{
	// TODO: Load different file based on which level we are on
	myTiledParser = std::make_unique<TiledParser>(aMapPath);
}

GameScene::GameScene() = default;
GameScene::~GameScene() = default;

void GameScene::Init()
{
	myTga2dLogoSprite = std::make_shared<SpriteWrapper>("Sprites/tga_logo.dds");

	myTag = GameObjectTag::Level_1;


	//myTiledParser = std::make_unique<TiledParser>("Maps/test_map.json");
	myTiledRenderer = std::make_unique<TiledRenderer>(myTiledParser.get());
	myTiledCollision = std::make_unique<TiledCollision>(myTiledParser.get());
	myCollisionManager = std::make_unique<CollisionManager>(myTiledCollision.get());
	myTiledEntities = std::make_unique<TiledEntities>(myTiledParser.get(), this);

	myMinimap = std::make_unique<Minimap>(myTiledParser.get(), myTiledCollision.get());

	for (size_t i = 0; i < 1; ++i)
	{
		AddGameObject(std::make_shared<GameObject>(this));
		myGameObjects[i]->Init();
		myGameObjects[i]->SetPosition({ 800.0f * (i + 1) , 1080.0f / 2.0f + 100.f});
	}

	myPlayer = std::make_shared<Player>(this);
	myPlayer->Init();

	myEnemyManager = std::make_unique<EnemyManager>(this, myMinimap.get());

	myMinimap->AddObject(myPlayer.get(), Minimap::MapObjectType::Player);

	GetCamera()->SetLevelBounds(AABB(CU::Vector2<float>(), CU::Vector2<float>(myTiledParser->GetWidth(), myTiledParser->GetHeight())));
	GetCamera()->SetPosition(CU::Vector2<float>());

	myTiledEntities->SpawnEntities();

	//myForeground = std::make_unique<Foreground>();
	//myForeground->Init();
	//myBackground = std::make_shared<SpriteWrapper>("Sprites/parallax/background01.dds");
	//myBackground->SetPosition(CU::Vector2(Metrics::GetReferenceSize().x * 0.5f, Metrics::GetReferenceSize().y * 0.5f));

	//myDialogueBox = std::make_shared<DialogueBox>(this); // temp
	//myDialogueBox->Init(myTag, "PlayerTest1");
	//myDialogueBox->SetPosition({405.0f,270.0f});
	//AddGameObject(myDialogueBox);
	
	const TiledEntity* playerSpawn = myTiledEntities->FindEntityWithType("PlayerSpawn");
	if (playerSpawn != nullptr)
	{
		myPlayer->SetPosition(playerSpawn->GetPosition());
		GetCamera()->SetPosition(playerSpawn->GetPosition());
	}

}

void GameScene::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	//myForeground->Update(aDeltaTime, myPlayer->GetPosition(), myPlayer->GetSpeed());

	Scene::Update(aDeltaTime, anUpdateContext);
	myPlayer->Update(aDeltaTime, anUpdateContext);

	myMinimap->SetGameView(GetCamera()->GetViewBounds());

	myCollisionManager->Update();

	//Removal of marked GameObjects
	myEnemyManager->Update(aDeltaTime, anUpdateContext);
	Scene::RemoveMarkedObjects();

	//temp
	myEnemyManager->AddTargetToAllEnemies(myPlayer);
}

void GameScene::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	Scene::Render(aRenderQueue, aRenderContext);

	/*RenderCommand renderCommand = RenderCommand(myBackground);
	aRenderQueue->Queue(renderCommand);*/

	aRenderQueue->Queue(RenderCommand(myTga2dLogoSprite));
	myPlayer->Render(aRenderQueue, aRenderContext);
	myTiledRenderer->Render(aRenderQueue, aRenderContext);

	myMinimap->Render(aRenderQueue);
	//myForeground->Render(aRenderQueue, aRenderContext);

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
