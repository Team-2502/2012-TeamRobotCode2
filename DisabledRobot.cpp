#include "DisabledRobot.h"
#include "RobotError.h"

DiabledRobot::DisabledRobot()
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

RobotError* lastError()
{
	return err;
}
