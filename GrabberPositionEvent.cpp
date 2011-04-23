#include "GrabberPositionEvent.h"

GrabberPositionEvent::GrabberPositionEvent(double m, EventListener* l)
{
	m_meters = m;
	listen = l;
}

EventListener* GrabberPositionEvent::sender()
{
	return listen;
}

double GrabberPositionEvent::report()
{
	return m_meters;
}
