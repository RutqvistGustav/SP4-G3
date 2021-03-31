#pragma once

#include "TriggerVolume.h"

class GoalZone :
	public TriggerVolume
{
public:

	GoalZone(Scene* aScene);

	virtual void TriggerEnter(GameObject* aGameObject) override;

};
