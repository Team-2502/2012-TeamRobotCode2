#include "TeleoperatedRobot.h"

TeleoperatedRobot::TeleoperatedRobot(DriveType type)
{
	drive = new DriverWrapper(type);
	myError = RobotError::NoError();
	lastGyroReading = 0.0;
}

TeleoperatedRobot::~TeleoperatedRobot()
{
	delete drive;
	delete myError;
}

bool TeleoperatedRobot::handle(Event *e)
{
	bool ret = false;
	switch(static_cast<int>(e->type()))
	{
		case JoystickPosition:
			drive->Drive(static_cast<JoystickPositionEvent*>(e)->x(),
						 static_cast<JoystickPositionEvent*>(e)->y(),
						 static_cast<JoystickPositionEvent*>(e)->twist(),
						 lastGyroReading);
			break;
		case GyroAngle:
			lastGyroReading = static_cast<GyroAngleEvent*>(e)->angle();
			break;
		default:
			if(myError) {
				delete myError;
				myError = new RobotError(Warning, "TeleoperatedRobot received unknown event.");
			}
			break;
	}
	return ret;
}
