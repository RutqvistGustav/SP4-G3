#pragma once

#include "GameMessage.h"

#include <unordered_map>
#include <vector>

class IGameMessageSubscriber;

class GameMessenger
{
public:

	void Subscribe(const GameMessage aMessage, IGameMessageSubscriber* aSubscriber);
	void Unsubscribe(const GameMessage aMessage, IGameMessageSubscriber* aSubscriber);

	void Send(const GameMessage aMessage, const void* someMessageData);

private:

	static constexpr std::size_t ourDefaultPerEventSubscriberCount = 12;

	// NOTE: If needed modify data structure for faster operations
	std::unordered_map<GameMessage, std::vector<IGameMessageSubscriber*>> myMessageSubscribers;

};

