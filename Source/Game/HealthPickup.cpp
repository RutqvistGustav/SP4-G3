#include "stdafx.h"
#include "HealthPickup.h"
#include "Collectable.h"
#include "Player.h"
#include "Scene.h"
#include "GlobalServiceProvider.h"
#include "JsonManager.h"

HealthPickup::HealthPickup(Scene* aScene)
	: Collectable(aScene)
{
	myHealingValue = 1;
	//InitWithJson(GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData());
}

void HealthPickup::OnCollect(Player* aPlayer)
{
	aPlayer->AddHealth(myHealingValue);
}
