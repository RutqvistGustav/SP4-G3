#pragma once
#include "Collectable.h"
class PowerUp :
    public Collectable
{
public:
    enum class PowerUpType
    {
        Berserk,
        SniperShot
    };

    PowerUp(Scene* aScene, PowerUpType aPowerUpType);
    void OnCollect(Player* aPlayer) override;

private:
    PowerUpType* myPowerUpType;
};

