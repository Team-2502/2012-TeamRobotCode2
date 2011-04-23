#include "DisabledRobot.h"
#include "DisplayWrapper.h"
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
	DisplayWrapper::GetInstance()->PrintfLine(0,"Robot Disabled.");
	DisplayWrapper::GetInstance()->Output();
	return true;
}

RobotError* DisabledRobot::lastError()
{
	return err;
}
