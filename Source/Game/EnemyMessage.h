#pragma once

#include "GenericGameMessageSubscriber.h"
#include "EnemyFactory.h"
#include "PowerUpType.h"
#include <Vector.hpp>
class GameObject;

struct EnemyMessageData
{
	EnemyType myEnemyType;
	CU::Vector2<float> mySpawnPosition;
	std::shared_ptr<GameObject> myTarget;
	PowerUpType myLootType;
};

using EnemyMessage = GenericGameMessageSubscriber<EnemyMessageData>;
