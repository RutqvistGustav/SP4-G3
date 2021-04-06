#include "stdafx.h"
#include "PowerUp.h"
#include "JsonManager.h"
#include "GlobalServiceProvider.h"
#include "Player.h"

PowerUp::PowerUp(Scene* aScene, PowerUpType aPowerUpType)
	: Collectable(aScene)
	, myPowerUpType(aPowerUpType)
{
	if (aPowerUpType == PowerUpType::Berserk)
	{
		InitWithJson(GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("Animations/BerserkerPickup.json"));
	}
	if (aPowerUpType == PowerUpType::HealthPickup)
	{
		InitWithJson(GetScene()->GetGlobalServiceProvider()->GetJsonManager()->GetData("Animations/HealthPickup.json"));
	}
}

void PowerUp::OnCollect(Player* aPlayer)
{
	aPlayer->ActivatePowerUp(myPowerUpType);
}
