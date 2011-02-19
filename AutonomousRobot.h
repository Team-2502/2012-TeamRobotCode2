#ifndef AUTONOMOUS_ROBOT
#define AUTONOMOUS_ROBOT

#include "RobotMode.h"
#include "Event.h"
#include "DriverWrapper.h"
//#include "Arm.h"

enum AutonomousState {
	TrackLine,
	PlaceTube
};

enum LineDirection {
	LeftLine,
	RightLine
};

class AutonomousRobot : public RobotMode
{
	public:
		AutonomousRobot();
		~AutonomousRobot();
		
		bool handle(Event *e);
		RobotError* lastError();
		
		void setLineDirection(LineDirection ld);
		
	private:
		DriverWrapper *drive;
		RobotError *myError;
		float lastGyroReading;
		//Arm *myArm;
		LineDirection l;
		AutonomousState myState;
};

#endif
