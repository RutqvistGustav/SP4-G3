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

#include "MathHelper.h"

//Managers
#include "CollisionManager.h"
#include "EnemyManager.h"
#include "ParticleEffectManager.h"

#include "LevelManagerProxy.h"

#include "TiledParser.h"
#include "TiledRenderer.h"
#include "TiledCollision.h"
#include "TiledEntities.h"

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
	myTiledParser = std::make_unique<TiledParser>(myMapPath);
	myTiledRenderer = std::make_unique<TiledRenderer>(myTiledParser.get());
	myTiledCollision = std::make_unique<TiledCollision>(myTiledParser.get());
	myCollisionManager = std::make_unique<CollisionManager>(myTiledCollision.get());
	myTiledEntities = std::make_unique<TiledEntities>(myTiledParser.get(), this);

	myMapAABB = AABB(CU::Vector2<float>(0.0f, 0.0f), CU::Vector2<float>(myTiledParser->GetWidth(), myTiledParser->GetHeight()));
	myMapAABB.Expand({ 200.0f, 200.0f });

	myParallaxContainer = std::make_unique<ParallaxContainer>(this);

	// TODO: Read from json?
	myParallaxContainer->AddLayer(0.2f, GameLayer::ParallaxForeground, "Sprites/parallax/dust_bot.dds");
	myParallaxContainer->AddLayer(0.2f, GameLayer::ParallaxForeground, "Sprites/parallax/dust_top.dds");

	myParallaxContainer->AddLayer(0.03f, GameLayer::ParallaxBackground + 1, "Sprites/parallax/Background/parallax_bg_2.dds")
		.SetRepeatBehaviour(ParallaxLayer::RepeatBehaviour::Horizontal)
		.SetOrigin(CU::Vector2<float>(Metrics::GetReferenceSize().x * 0.5f, myTiledParser->GetHeight() - Metrics::GetReferenceSize().y * 18.0f));

	myParallaxContainer->AddLayer(0.05f, GameLayer::ParallaxBackground + 2, "Sprites/parallax/Background/parallax_bg_3.dds")
		.SetRepeatBehaviour(ParallaxLayer::RepeatBehaviour::Horizontal)
		.SetOrigin(CU::Vector2<float>(Metrics::GetReferenceSize().x * 0.5f, myTiledParser->GetHeight() - Metrics::GetReferenceSize().y * 18.0f));

	myParallaxDustLayers[0] = myParallaxContainer->GetLayer(0);
	myParallaxDustLayers[1] = myParallaxContainer->GetLayer(1);

	myBackground = std::make_shared<SpriteWrapper>("Sprites/parallax/Background/parallax_bg_1.dds");
	myBackground->SetPivot({ 0.0f, 0.0f });
	myBackground->SetPosition({ 0.0f, 0.0f });
	myBackground->SetSize({ myTiledParser->GetWidth(), myTiledParser->GetHeight() });
	myBackground->SetLayer(GameLayer::ParallaxBackground);

	myCollisionManager->IgnoreCollision(CollisionLayer::MapSolid, CollisionLayer::Default);
	myCollisionManager->IgnoreCollision(CollisionLayer::MapSolid, CollisionLayer::HUD);
	myCollisionManager->IgnoreCollision(CollisionLayer::Entity, CollisionLayer::Entity);

	myPlayer = std::make_shared<Player>(this);
	myPlayer->Init();

	myEnemyManager = std::make_unique<EnemyManager>(this);
	myCollectibleManager = std::make_unique<CollectibleManager>(this);
	myParticleEffectManager = std::make_unique<ParticleEffectManager>(this);

	GetCamera()->SetLevelBounds(AABB(CU::Vector2<float>(), CU::Vector2<float>(myTiledParser->GetWidth(), myTiledParser->GetHeight())));
	GetCamera()->SetPosition(CU::Vector2<float>());

	myTiledEntities->SpawnEntities();

	const TiledEntity* playerSpawn = myTiledEntities->FindEntityWithType("PlayerSpawn");
	if (playerSpawn != nullptr)
	{
		myPlayer->SetPosition(playerSpawn->GetPosition());
		GetCamera()->SetPosition(playerSpawn->GetPosition());

		if (playerSpawn->HasProperty("StartDialogID"))
		{
			const std::string startDialogID = playerSpawn->GetProperty("StartDialogID");

			if (!startDialogID.empty())
			{
				std::shared_ptr<DialogueBox> dialogBox = std::make_shared<DialogueBox>(this, true);
				dialogBox->Init(startDialogID);
				dialogBox->SetPosition(myPlayer->GetPosition());
				dialogBox->SetTriggerSize(CU::Vector2<float>(200.0f, 200.0f));

				AddGameObject(dialogBox);

				// NOTE: Fake an interact event to trigger the initial dialog
				dialogBox->OnInteract(myPlayer.get());
			}
		}
	}

	GetGlobalServiceProvider()->GetGameMessenger()->Subscribe(GameMessage::StageClear, this);
}

void GameScene::OnExit()
{
	GetGlobalServiceProvider()->GetGameMessenger()->Unsubscribe(GameMessage::StageClear, this);
}

void GameScene::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	if (myIsGamePaused == false)
	{
		Scene::Update(aDeltaTime, anUpdateContext);
		myPlayer->Update(aDeltaTime, anUpdateContext);

		//Removal of marked GameObjects
		myEnemyManager->DeleteMarkedEnemies();
		myCollectibleManager->DeleteMarkedCollectables();

		UpdateCustomParallaxEffects(aDeltaTime);
		CheckOutOfBounds();

		//temp
		myEnemyManager->AddTargetToAllEnemies(myPlayer);
	}
	else
	{
		myPauseMenu->Update(aDeltaTime, anUpdateContext);
	}
	StartPauseMenu(anUpdateContext);
	StopPauseMenu();

	Scene::RemoveMarkedObjects();
	myCollisionManager->Update();
}

void GameScene::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	Scene::Render(aRenderQueue, aRenderContext);

	aRenderQueue->Queue(RenderCommand(myBackground));

	myPlayer->Render(aRenderQueue, aRenderContext);
	myTiledRenderer->Render(aRenderQueue, aRenderContext);

	myParallaxContainer->Render(aRenderQueue);

	if(myIsGamePaused) myPauseMenu->Render(aRenderQueue, aRenderContext);

#ifdef _DEBUG
	myCollisionManager->RenderDebug(aRenderQueue, aRenderContext);
#endif //_DEBUG
}

GameMessageAction GameScene::OnMessage(const GameMessage aMessage, const StageClearMessageData* /*someMessageData*/)
{
	assert(aMessage == GameMessage::StageClear);

	GetLevelManagerProxy()->TransitionNextLevel();

	return GameMessageAction::Keep;
}

void GameScene::UpdateCustomParallaxEffects(float aDeltaTime)
{
	constexpr float rotationSpeed = 90.0f;
	constexpr float offsetAmplitude = 20.0f;

	myParallaxDustRotation += rotationSpeed * aDeltaTime;

	const float radRotation = MathHelper::DegToRad(myParallaxDustRotation);
	const CU::Vector2<float> offset0 = CU::Vector2<float>(std::cos(radRotation), std::sin(radRotation)) * offsetAmplitude;
	const CU::Vector2<float> offset1 = CU::Vector2<float>(std::cos(-radRotation * 0.8f), std::sin(-radRotation * 0.8f)) * offsetAmplitude;

	myParallaxDustLayers[0]->SetLayerOffset(offset0);
	myParallaxDustLayers[1]->SetLayerOffset(offset1);
}

void GameScene::CheckOutOfBounds()
{
	const CU::Vector2<float> playerPosition = myPlayer->GetPosition();

	if (!myMapAABB.Contains(playerPosition))
	{
		// NOTE: Out of bounds => Kill player
		myPlayer->TakeDamage(999999);
	}
}

void GameScene::StartPauseMenu(UpdateContext& anUpdateContext)
{
	if (anUpdateContext.myInputInterface->IsPressingPause() && myPauseMenu == nullptr)
	{
		myIsGamePaused = true;
		myPauseMenu = std::make_unique<PauseMenu>();
		myPauseMenu->OnEnter(GetSceneManagerProxy(), GetLevelManagerProxy(), GetGlobalServiceProvider());
		myPauseMenu->Init();
	}
}

void GameScene::StopPauseMenu()
{
	if (myPauseMenu != nullptr)
	{
		if (myPauseMenu->IsGamePaused() == false)
		{
			myPauseMenu.reset();
			myIsGamePaused = false;
		}
	}
}
