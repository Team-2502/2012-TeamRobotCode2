#ifndef DISABLED_ROBOT
#define DISABLED_ROBOT

#include "RobotMode.h"
#include "RobotError.h"

class DisabledRobot : public RobotMode
{
public:
	DisabledRobot() { err = RobotError::NoError(); }
	~DisabledRobot() { delete err; }
	bool handle(Event *) { return true; }
	RobotError* lastError() { return err; }
	
private:
	RobotError* err;
};

#endif
