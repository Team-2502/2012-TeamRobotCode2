#ifndef VISION_EVENT_H
#define VISION_EVENT_H

#include "Event.h"
#include "VisionRoutines.h"
class EventListener;

class VisionEvent : public Event
{
	public:
		VisionEvent(TargetReport rpt, EventListener* l);
		~VisionEvent() {}
		
		EventType type() { return TargetEvent; }
		EventListener* sender();
		TargetReport report();
		
	private:
		TargetReport m_rpt;
		EventListener *listen;
};

#endif
