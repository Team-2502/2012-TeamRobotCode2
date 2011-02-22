#include "EventListener.h"
#include "LineEvent.h"

LineTrackingEvent::LineTrackingEvent(int state, EventListener* l)
{
	m_state = state;
	listen = l;
}

EventListener* LineTrackingEvent::sender()
{
	return listen;
}

int LineTrackingEvent::state()
{
	return m_state;
}
