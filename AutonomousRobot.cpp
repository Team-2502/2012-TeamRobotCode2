#include "VisionEvent.h"
#include "RobotError.h"
#include "AutonomousRobot.h"
#include "DisplayWrapper.h"
#include "DriverStationLCD.h"
#include "LineEvent.h"
#include "Arm.h"
#include "config.h"

AutonomousRobot::AutonomousRobot()
{
	drive = new DriverWrapper(Tank);
	myError = RobotError::NoError();
	lastGyroReading = 0.0;
	l = LeftLine;
	myState = PlaceTube;
}

AutonomousRobot::~AutonomousRobot()
{
	drive->Drive(0,0,0);
	delete drive;
	delete myError;
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
	bool moveToDrop = false;
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
			moveToDrop = false;
			if(e->type() == TargetEvent)
			{
				ve = static_cast<VisionEvent*>(e);
				if(ve->report().y > (int)(2.0*YRESOLUTION/3.0)) { //top third
					Arm::GetInstance()->setSpeed(-0.5);
				} else if(ve->report().y < (int)(YRESOLUTION/3.0)) { //bottom third
					Arm::GetInstance()->setSpeed(0.5);
				} else { //In middle third
					Arm::GetInstance()->setSpeed(0.0);
					moveToDrop = true;
				}
				if(ve->report().area > 0.8*XRESOLUTION*YRESOLUTION) { //If the peg takes up 80% of the camera, then stop.
					drive->Drive(0,0,0);
				} else {
					moveToDrop = false;
				}
				if(moveToDrop)
					myState = DropTube;
			}
			break;
		case DropTube:
			Arm::GetInstance()->setSpeed(0.0);
			Wait(0.5);
			drive->Drive(0,-0.4,0);
			myState = Done;
			break;
		default:
			if(myError) {
				delete myError; myError = 0;
			}
			myError = new RobotError(Warning, "AutonomousRobot received unknown event.");
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
