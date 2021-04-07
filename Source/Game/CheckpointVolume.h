#pragma once

#include "TriggerVolume.h"

class CheckpointVolume :
	public TriggerVolume
{
public:

	CheckpointVolume(Scene* aScene);

	virtual void TriggerEnter(GameObject* aGameObject) override;

private:

	bool myIsUsed{};

};
