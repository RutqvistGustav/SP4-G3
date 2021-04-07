#pragma once

#include "SimpleEventObserver.h"

#include <vector>

template <typename EventData>
class SimpleEventSubject
{
public:

	void Subscribe(SimpleEventObserver<EventData>* anObserver)
	{
		myObservers.push_back(anObserver);
	}

	void Unsubscribe(SimpleEventObserver<EventData>* anObserver)
	{
		auto it = std::find(myObservers.begin(), myObservers.end(), anObserver);
		if (it != myObservers.end())
		{
			myObservers.erase(it);
		}
	}

	void Notify(EventData someEventData)
	{
		// NOTE: Protection against modifications to myObservers while inside loop?

		for (auto observer : myObservers)
		{
			observer->OnEvent(someEventData);
		}
	}

private:

	std::vector<SimpleEventObserver<EventData>*> myObservers;

};
