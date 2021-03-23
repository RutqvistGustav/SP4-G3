#pragma once

#include "GenericGameMessageSubscriber.h"
#include "EnemyFactory.h"
#include <Vector.hpp>
class GameObject;

struct EnemyMessageData
{
	EnemyFactory::EnemyType myEnemyType;
	CU::Vector2<float> mySpawnPosition;
	std::shared_ptr<GameObject> myTarget;
};

using EnemyMessage = GenericGameMessageSubscriber<EnemyMessageData>;
