#ifndef AUTONOMOUS_ROBOT
#define AUTONOMOUS_ROBOT

#include "RobotMode.h"
#include "Event.h"
#include "DriverWrapper.h"
//#include "Arm.h"

enum AutonomousState {
	TrackLine,
	PlaceTube,
	DropTube,
	Done,
};

enum LineDirection {
	LeftLine,
	RightLine
};

class AutonomousRobot : public RobotMode
{
	enum LineTrackingState {
		Opposite=0,
		Straight=1,
		AtTheT=7,
	};
	enum ForkSide {
		Left=1,
		Right=-1
	};
	public:
		AutonomousRobot();
		~AutonomousRobot();
		
		bool handle(Event *e);
		RobotError* lastError();
		
		void setLineDirection(LineDirection ld);
		void disable();
		
	private:
		DriverWrapper *drive;
		RobotError *myError;
		float lastGyroReading;
		//Arm *myArm;
		LineDirection l;
		AutonomousState myState;
};

#endif
