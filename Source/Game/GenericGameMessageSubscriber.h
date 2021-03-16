#pragma once

#include "IGameMessageSubscriber.h"

template <typename DataType>
class GenericGameMessageSubscriber : protected IGameMessageSubscriber
{
protected:

	static_assert(!std::is_void_v<DataType>, "DataType cannot be void!");

	virtual GameMessageAction OnMessage(const GameMessage aMessage, const DataType* someMessageData) = 0;

	virtual GameMessageAction OnMessage(const GameMessage aMessage, const void* someMessageData) override
	{
		// NOTE: Usage of reinterpret_cast should be safe here because we expect a derived class to
		// specify DataType in such a way that when it subscribes it will always be to an event that sends that type of message
		
		return OnMessage(aMessage, reinterpret_cast<const DataType*>(someMessageData));
	}

};