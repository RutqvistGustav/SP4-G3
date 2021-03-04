#pragma once

template <typename EventType, typename EventData>
class EventObserver
{
public:

	virtual void OnEvent(EventType anEvent, EventData someEventData) = 0;

};
