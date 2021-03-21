#pragma once

#include "GenericGameMessageSubscriber.h"
#include "EnemyFactory.h"
#include <Vector.hpp>


struct EnemyMessageData
{
	EnemyFactory::EnemyType myEnemyType;
	CU::Vector2<float> mySpawnPosition;
};

using EnemyMessage = GenericGameMessageSubscriber<EnemyMessageData>;
