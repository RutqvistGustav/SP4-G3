#pragma once
#pragma once

#include "GenericGameMessageSubscriber.h"
#include "PowerUpType.h"
#include <Vector.hpp>
class GameObject;

struct EnemyDeathMessageData
{
	CU::Vector2<float> myDeathPosition;
	PowerUpType myLootType = PowerUpType::None;
};

using EnemyDeathMessage = GenericGameMessageSubscriber<EnemyDeathMessageData>;
