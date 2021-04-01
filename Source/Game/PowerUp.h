#pragma once
#include "Collectable.h"
#include "PowerUpType.h"

class PowerUp :
    public Collectable
{
public:
    PowerUp(Scene* aScene, PowerUpType aPowerUpType);
    void OnCollect(Player* aPlayer) override;

private:
    PowerUpType myPowerUpType;
};

