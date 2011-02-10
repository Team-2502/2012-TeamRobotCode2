#ifndef DISABLED_ROBOT
#define DISABLED_ROBOT

#include "RobotMode.h"
class RobotError;

class DisabledRobot : public RobotMode
{
public:
	DisabledRobot();
	~DisabledRobot();
	bool handle(Event *);
	RobotError* lastError();
	
private:
	RobotError* err;
};

#endif
