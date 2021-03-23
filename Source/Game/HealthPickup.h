#pragma once
#include "Collectable.h"
class HealthPickup : public Collectable
{
public:
	HealthPickup(Scene* aScene);

	virtual void OnCollect(Player* aPlayer) override;

private:
	int myHealingValue;
};

