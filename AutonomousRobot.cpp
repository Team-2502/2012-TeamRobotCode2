#include "VisionEvent.h"
#include "RobotError.h"
#include "AutonomousRobot.h"
#include "DisplayWrapper.h"
#include "config.h"

AutonomousRobot::AutonomousRobot()
{
	drive = new DriverWrapper(Tank);
	myError = RobotError::NoError();
	lastGyroReading = 0.0;
	myArm = new Arm;
	l = LeftLine;
	myState = PlaceTube;
}

AutonomousRobot::~AutonomousRobot()
{
	delete drive;
	delete myError;
	delete myArm;
}

bool AutonomousRobot::handle(Event *e)
{
	VisionEvent *ve = 0;
	switch(myState)
	{
		case TrackLine:
			DisplayWrapper::GetInstance()->PrintfLine(4,"Auto: Implement LT.");
			DisplayWrapper::GetInstance()->Output();
			break;
		case PlaceTube:
			if(e->type() == TargetEvent)
			{
				ve = static_cast<VisionEvent*>(e);
				if(ve->report().y > (int)(2.0*YRESOLUTION/3.0)) {
					//myArm->setHeight(sideSecond);
					DisplayWrapper::GetInstance()->PrintfLine(4,"Auto: Arm up.");
					DisplayWrapper::GetInstance()->Output();
				} else if(ve->report().y < (int)(YRESOLUTION/3.0)) {
					//myArm->setHeight(sideFirst);
					DisplayWrapper::GetInstance()->PrintfLine(4,"Auto: Arm down.");
					DisplayWrapper::GetInstance()->Output();
				}
			}
			break;
		default:
			if(myError) {
				delete myError; myError = 0;
				myError = new RobotError(Warning, "AutonomousRobot received unknown event.");
			}
			return false;
			break;
	}
	return true;
}

RobotError* AutonomousRobot::lastError()
{
	return myError;
}

void AutonomousRobot::setLineDirection(LineDirection ld)
{
	l = ld;
}
