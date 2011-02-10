#ifndef ROBOTMODE_H
#define ROBOTMODE_H

class RobotError;
class Event;

class RobotMode
{
public:
	virtual ~RobotMode() {}
	virtual bool handle(Event *) = 0;
	virtual RobotError* lastError() = 0;
};

#endif
