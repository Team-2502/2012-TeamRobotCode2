#ifndef TELEOPERATED_ROBOT
#define TELEOPERATED_ROBOT

#include "RobotMode.h"
#include "Event.h"
#include "DriverWrapper.h"

class Timer;
class Minibot;
class Arm;

enum Button
{
	trigger=1,
	shapeShifter=2,
	sideFirstButton=3,
	middleFirstButton=4,
	highResButton=12,
	sideSecondButton=5,
	middleSecondButton=6,
	deployButton=7,
	gyroResetButton=8,
	targetSnapButton=11
};

class TeleoperatedRobot : public RobotMode
{
	public:
		TeleoperatedRobot(DriveType type = Mecanum);
		~TeleoperatedRobot();
		
		bool handle(Event *e);
		RobotError* lastError();
		
		void disable();
		
	private:
		DriverWrapper *drive;
		RobotError *myError;
		float lastGyroReading;
		float gyroCorrection;
		int encoderValue;
		Timer* minibotTimer;
		Minibot* minibot;
		Arm* arm;
};

#endif
