#include "stdafx.h"
#include "HUD.h"
#include "HealthBar.h"
#include "Scene.h"
#include "CollisionManager.h"

HUD::HUD(Scene* aScene)
	: GameObject(aScene)
{
	myHealthBar = std::make_unique<HealthBar>(aScene);

	//CollisionManager::GetInstance()->RemoveCollider(myCollider);
	aScene->GetCollisionManager()->RemoveCollider(myCollider);
	myCollider.reset();
}

void HUD::Update(CU::Vector2<float> aPlayerPosition)
{
	myHealthBar->Update(aPlayerPosition);
}

void HUD::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	myHealthBar->Render(aRenderQueue, aRenderContext);
}

void HUD::OnCollision(GameObject*)
{

}

HealthBar* HUD::GetHealthBar()
{
	return myHealthBar.get();
}
