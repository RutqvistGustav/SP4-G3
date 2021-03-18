#pragma once

#include "GameMessage.h"
#include "GameMessageAction.h"

class IGameMessageSubscriber
{
public:

	virtual ~IGameMessageSubscriber() = 0 {}

	virtual GameMessageAction OnMessage(const GameMessage aMessage, const void* someMessageData) = 0;

};
