#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

#include "Event.h"
#include "RobotError.h"

class EventListener
{
	public:
		virtual ~EventListener() {}
		virtual Event* getEvent(int) = 0;
		virtual int getMessageQuantity() = 0;
};

#endif
