#pragma once

#include "EventObserver.h"

#include <vector>

template <typename EventType, typename EventData>
class EventSubject
{
public:

	void Subscribe(EventObserver<EventType, EventData>* anObserver)
	{
		myObservers.push_back(anObserver);
	}

	void Unsubscribe(EventObserver<EventType, EventData>* anObserver)
	{
		auto it = std::find(myObservers.begin(), myObservers.end(), anObserver);
		if (it != myObservers.end())
		{
			myObservers.erase(it);
		}
	}

	void Notify(EventType anEvent, EventData someEventData)
	{
		// NOTE: Protection against modifications to myObservers while inside loop?

		for (auto observer : myObservers)
		{
			observer->OnEvent(anEvent, someEventData);
		}
	}

private:

	std::vector<EventObserver<EventType, EventData>*> myObservers;

};
