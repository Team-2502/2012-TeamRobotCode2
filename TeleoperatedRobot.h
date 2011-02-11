#ifndef TELEOPERATED_ROBOT
#define TELEOPERATED_ROBOT

#include "RobotMode.h"
#include "Event.h"
#include "DriverWrapper.h"
#include "DisplayWrapper.h"

class TeleoperatedRobot : public RobotMode
{
	public:
		TeleoperatedRobot(DriveType type = Mecanum);
		~TeleoperatedRobot();
		
		bool handle(Event *e);
		RobotError* lastError();
		
	private:
		DriverWrapper *drive;
		DisplayWrapper *display;
		RobotError *myError;
		float lastGyroReading;
};

#endif
