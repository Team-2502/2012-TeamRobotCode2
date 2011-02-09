#ifndef ROBOTMODE
#define ROBOTMODE

class Event;
class RobotError;

class RobotMode
{
public:
	virtual ~RobotMode() {}
	virtual bool handle(Event *) = 0;
	virtual RobotError* lastError() = 0;
};

#endif
