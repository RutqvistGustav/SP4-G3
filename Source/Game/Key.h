#pragma once

#include "Collectable.h"

class Key : public Collectable
{
public:
	Key(Scene* aScene, PowerUpType aPowerupType);
	virtual void InitWithJson(const JsonData& someProperties) override;
	virtual void OnCollect(Player* aPlayer) override;
};
