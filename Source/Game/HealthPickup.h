#pragma once
#include "Collectable.h"
class HealthPickup : public Collectable
{
public:
	HealthPickup(Scene* aScene, PowerUpType aPowerupType);

	virtual void InitWithJson(const JsonData& someProperties) override;
	virtual void OnCollect(Player* aPlayer) override;

private:
	int myHealingValue;
};

