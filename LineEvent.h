#ifndef LINE_TRACKING_EVENT
#define LINE_TRACKING_EVENT

#include "Event.h"

class EventListener;

enum LineTrackingState
{
	LeftFork=1,
	Forward=2,
	RightFork=4
};

class LineTrackingEvent : public Event
{
	public:
		LineTrackingEvent(int state, EventListener* l);
		~LineTrackingEvent() {}
		
		EventType type() { return LineTracking; }
		EventListener* sender();
		
		int state();
		
	private:
		int m_state;
		EventListener *listen;
};

#endif
