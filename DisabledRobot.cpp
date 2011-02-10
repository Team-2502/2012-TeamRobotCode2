#include "DisabledRobot.h"
#include "RobotError.h"

DisabledRobot::DisabledRobot()
{
	err = RobotError::NoError();
}

DisabledRobot::~DisabledRobot()
{
	delete err;
}

bool DisabledRobot::handle(Event*)
{
	return true;
}

RobotError* DisabledRobot::lastError()
{
	return err;
}
