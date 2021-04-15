#pragma once

#include "GenericGameMessageSubscriber.h"
#include "PowerUpType.h"
#include <Vector.hpp>
class GameObject;

struct CollectableMessageData
{
	PowerUpType myLootType = PowerUpType::None;
	CU::Vector2<float> mySpawnPosition;
	std::string myDialogID;
};

using CollectableMessage = GenericGameMessageSubscriber<CollectableMessageData>;