#pragma once
#include "Collectable.h"
#include "PowerUpType.h"

class PowerUp :
    public Collectable
{
public:
    PowerUp(Scene* aScene, PowerUpType aPowerUpType);
    virtual void InitWithJson(const JsonData& someProperties) override;
    void OnCollect(Player* aPlayer) override;

private:
    PowerUpType myPowerUpType;
};

