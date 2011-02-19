#ifndef TELEOPERATED_ROBOT
#define TELEOPERATED_ROBOT

#include "RobotMode.h"
#include "Event.h"
#include "DriverWrapper.h"

class TeleoperatedRobot : public RobotMode
{
	public:
		TeleoperatedRobot(DriveType type = Mecanum);
		~TeleoperatedRobot();
		
		bool handle(Event *e);
		RobotError* lastError();
		
	private:
		DriverWrapper *drive;
		RobotError *myError;
		float lastGyroReading;
		Servo* servo;
};

#endif
