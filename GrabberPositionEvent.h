#ifndef GRABBER_EVENT_H
#define GRABBER_EVENT_H

#include "Event.h"
class EventListener;

class GrabberPositionEvent : public Event
{
	public:
		GrabberPositionEvent(double m, EventListener* l);
		~GrabberPositionEvent() {}
		
		EventType type() { return GrabberEvent; }
		EventListener* sender();
		double report();
		
	private:
		double m_meters;
		EventListener *listen;
};

#endif
