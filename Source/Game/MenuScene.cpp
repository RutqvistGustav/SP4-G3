#include "stdafx.h"
#include "MenuScene.h"

#include "CollisionManager.h"

#include "Metrics.h"

#include "MousePointer.h"

#include "Camera.h"

MenuScene::MenuScene() = default;

MenuScene::~MenuScene() = default;

void MenuScene::Init()
{
	myCollisionManager = std::make_unique<CollisionManager>();

	myMousePointer = std::make_unique<MousePointer>(this);
	myMousePointer->Init();

	GetCamera()->SetLevelBounds(AABB({ 0.0f, 0.0f }, Metrics::GetReferenceSize()));
	GetCamera()->SetPosition(Metrics::GetReferenceSize() * 0.5f);
}

void MenuScene::Update(const float aDeltaTime, UpdateContext& anUpdateContext)
{
	Scene::Update(aDeltaTime, anUpdateContext);

	myMousePointer->Update(aDeltaTime, anUpdateContext);

	myCollisionManager->Update();
}

void MenuScene::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	Scene::Render(aRenderQueue, aRenderContext);

	myMousePointer->Render(aRenderQueue, aRenderContext);
}

void MenuScene::AddInterfaceElement(std::shared_ptr<GameObject> anElement)
{
	AddGameObject(anElement);
}
