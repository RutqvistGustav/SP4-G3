#pragma once

template <typename EventData>
class SimpleEventObserver
{
public:

	virtual void OnEvent(EventData someEventData) = 0;

};
