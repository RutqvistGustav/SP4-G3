#include "stdafx.h"
#include "HUD.h"

#include "HealthBar.h"
#include "Scene.h"
#include "AmmoCounter.h"
#include "UIHook.h"
#include "CollisionManager.h"

HUD::HUD(Scene* aScene, Health* aHealthInterface, Shotgun* aShotgun)
	: GameObject(aScene)
{
	myHealthBar = std::make_unique<HealthBar>(aScene, aHealthInterface);
	myAmmoCounter = std::make_unique<AmmoCounter>(aScene, aShotgun);

	//CollisionManager::GetInstance()->RemoveCollider(myCollider);
	aScene->GetCollisionManager()->RemoveCollider(myCollider);
	myCollider.reset();
}

void HUD::Init()
{
	myHealthBar->Init();
	myAmmoCounter->Init();
}

void HUD::Update(const float aDeltaTime, CU::Vector2<float> aPlayerPosition)
{
	myHealthBar->Update(aDeltaTime, aPlayerPosition);
	myAmmoCounter->Update(aPlayerPosition);
}

void HUD::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	myHealthBar->Render(aRenderQueue, aRenderContext);
	myAmmoCounter->Render(aRenderQueue, aRenderContext);
}

HealthBar* HUD::GetHealthBar()
{
	return myHealthBar.get();
}

AmmoCounter* HUD::GetAmmoCounter()
{
	return myAmmoCounter.get();
}
