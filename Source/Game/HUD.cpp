#include "stdafx.h"
#include "HUD.h"
#include "HealthBar.h"

HUD::HUD(Scene* aScene)
	: GameObject(aScene)
{
	myHealthBar = std::make_unique<HealthBar>(aScene);
}

void HUD::Update(CU::Vector2<float> aPlayerPosition)
{
	myHealthBar->Update(aPlayerPosition);
}

void HUD::Render(RenderQueue* const aRenderQueue, RenderContext& aRenderContext)
{
	myHealthBar->Render(aRenderQueue, aRenderContext);
}

HealthBar* HUD::GetHealthBar()
{
	return myHealthBar.get();
}
