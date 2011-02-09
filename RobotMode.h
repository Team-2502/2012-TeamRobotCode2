#ifndef ROBOTMODE
#define ROBOTMODE

#include "Event.h"
#include "RobotError.h"

class RobotMode
{
public:
	virtual ~RobotMode() {}
	virtual bool handle(Event *) = 0;
	virtual RobotError* lastError() = 0;
};

#endif
