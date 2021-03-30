#include "stdafx.h"
#include "PowerUp.h"
#include "Player.h"

PowerUp::PowerUp(Scene* aScene, PowerUpType aPowerUpType)
	: Collectable(aScene)
	, myPowerUpType(aPowerUpType)
{
}

void PowerUp::OnCollect(Player* aPlayer)
{
	aPlayer->ActivatePowerUp(myPowerUpType);
}
