#include "stdafx.h"
#include "GameMessenger.h"

#include "IGameMessageSubscriber.h"

void GameMessenger::Subscribe(const GameMessage aMessage, IGameMessageSubscriber* aSubscriber)
{
	std::vector<IGameMessageSubscriber*>& subscribers = myMessageSubscribers[aMessage];

	if (subscribers.capacity() < GameMessenger::ourDefaultPerEventSubscriberCount)
	{
		subscribers.reserve(GameMessenger::ourDefaultPerEventSubscriberCount);
	}

	subscribers.push_back(aSubscriber);
}

void GameMessenger::Unsubscribe(const GameMessage aMessage, IGameMessageSubscriber* aSubscriber)
{
	auto messageIt = myMessageSubscribers.find(aMessage);
	if (messageIt != myMessageSubscribers.end())
	{
		std::vector<IGameMessageSubscriber*>& subscribers = messageIt->second;

		auto subscriberIt = std::find(subscribers.begin(), subscribers.end(), aSubscriber);
		if (subscriberIt != subscribers.end())
		{
			subscribers.erase(subscriberIt);
		}
	}
}

void GameMessenger::Send(const GameMessage aMessage, const void* someMessageData)
{
	auto messageIt = myMessageSubscribers.find(aMessage);
	if (messageIt != myMessageSubscribers.end())
	{
		std::vector<IGameMessageSubscriber*>& subscribers = messageIt->second;

		for (std::size_t i = 0; i < subscribers.size(); ++i)
		{
			GameMessageAction messageAction = subscribers[i]->OnMessage(aMessage, someMessageData);

			if (messageAction == GameMessageAction::Unsubscribe)
			{
				std::swap(subscribers[i], subscribers.back());

				subscribers.pop_back();

				--i;
			}
		}
	}
}
