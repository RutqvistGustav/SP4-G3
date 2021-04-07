#include "stdafx.h"
#include "CheckpointVolume.h"

#include "LevelManagerProxy.h"

#include <cassert>

CheckpointVolume::CheckpointVolume(Scene* aScene) :
	TriggerVolume(aScene, GameObjectTag::Player)
{}

void CheckpointVolume::TriggerEnter(GameObject* aGameObject)
{
	if (!myIsUsed)
	{
		myScene->GetLevelManagerProxy()->SaveCheckpoint();

		myIsUsed = true;
	}
}
