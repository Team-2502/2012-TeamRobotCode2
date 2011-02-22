#include "VisionEvent.h"

VisionEvent::VisionEvent(TargetReport rpt, EventListener* l)
{
	m_rpt = rpt;
	listen = l;
}

EventListener* VisionEvent::sender()
{
	return listen;
}

TargetReport VisionEvent::report()
{
	return m_rpt;
}
