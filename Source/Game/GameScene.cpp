#include "stdafx.h"
#include "GameScene.h"

#include "Player.h"

#include "Metrics.h"

#include "RenderCommand.h"
#include "RenderQueue.h"

#include "SpriteWrapper.h"

#include "CollisionManager.h"

GameScene::GameScene() = default;
GameScene::~GameScene() = default;

void GameScene::Init()
{
	myTga2dLogoSprite = std::make_shared<SpriteWrapper>("Sprites/tga_logo.dds");
	myTga2dLogoSprite->SetPosition(Metrics::GetReferenceSize() * 0.5f);

	myPlayer = std::make_unique<Player>(this);
	myPlayer->SetPosition({ 950.0f, 540.0f });
	myPlayer->Init();



	for (size_t i = 0; i < 10; ++i)
	{
		AddGameObject(std::make_shared<GameObject>(this));
		myGameObjects[i]->Init();
		myGameObjects[i]->SetPosition({ 1900.0f / (i + 1) , 1080.0f});
	}
	


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

}
