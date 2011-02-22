#include "VisionEvent.h"
#include "RobotError.h"
#include "AutonomousRobot.h"
#include "DisplayWrapper.h"
#include "DriverStationLCD.h"
#include "LineEvent.h"
#include "config.h"

AutonomousRobot::AutonomousRobot()
{
	drive = new DriverWrapper(Tank);
	myError = RobotError::NoError();
	lastGyroReading = 0.0;
	//myArm = new Arm;
	l = LeftLine;
	myState = PlaceTube;
}

AutonomousRobot::~AutonomousRobot()
{
	drive->Drive(0,0,0);
	delete drive;
	delete myError;
	//delete myArm;
}

void AutonomousRobot::disable()
{
	drive->Drive(0,0,0);
}

bool AutonomousRobot::handle(Event *e)
{
	VisionEvent *ve = 0;
	int ltState = 0;
	ForkSide side = DriverStation::GetInstance()->GetDigitalIn(1) ? Right : Left; //off = left, on = right
	switch(myState)
	{
		case TrackLine:
			if(e->type() == LineTracking) {
				DisplayWrapper::GetInstance()->PrintfLine(4,"Auto: Tracking Line.");
				DisplayWrapper::GetInstance()->Output();
				ltState = static_cast<LineTrackingEvent*>(e)->state();
				if(ltState == Opposite) {
					drive->Drive(0.5*side,0,0);
				} else if(ltState == Straight) {
					drive->Drive(0,0,5,0);
				} else if(ltState == AtTheT) {
					drive->Drive(0,0,0);
					myState = PlaceTube;
				} else {
					drive->Drive(-0.5*side,0,0);
				}
			}
			break;
		case PlaceTube:
			if(e->type() == TargetEvent)
			{
				ve = static_cast<VisionEvent*>(e);
				if(ve->report().y > (int)(2.0*YRESOLUTION/3.0)) { //top third
					//myArm->setHeight(sideSecond);
					DisplayWrapper::GetInstance()->PrintfLine(4,"Auto: Arm up.");
					DisplayWrapper::GetInstance()->Output();
				} else if(ve->report().y < (int)(YRESOLUTION/3.0)) { //bottom third
					//myArm->setHeight(sideFirst);
					DisplayWrapper::GetInstance()->PrintfLine(4,"Auto: Arm down.");
					DisplayWrapper::GetInstance()->Output();
				} else { //In middle third
					DisplayWrapper::GetInstance()->PrintfLine(4,"Auto: Arm down.");
					DisplayWrapper::GetInstance()->Output();
				}
				if(ve->report().area > 0.8*XRESOLUTION*YRESOLUTION) { //If the peg takes up 80% of the camera, then stop.
					drive->Drive(0,0,0);
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
