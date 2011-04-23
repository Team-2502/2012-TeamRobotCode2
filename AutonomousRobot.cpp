#include "VisionEvent.h"
#include "RobotError.h"
#include "AutonomousRobot.h"
#include "DisplayWrapper.h"
#include "DriverStationLCD.h"
#include "LineEvent.h"
#include "Arm.h"
#include "Grabber.h"
#include "config.h"

AutonomousRobot::AutonomousRobot()
{
	drive = new DriverWrapper(Mecanum);
	myError = RobotError::NoError();
	lastGyroReading = 0.0;
	l = LeftLine;
	myState = TrackLine;
	DisplayWrapper::GetInstance()->PrintfLine(0,"Auto: Initialized.");
	DisplayWrapper::GetInstance()->Output();
	
	Solenoid* power1 = new Solenoid(8,1);
	Solenoid* power2 = new Solenoid(8,2);
	Solenoid* power3 = new Solenoid(8,3);
	power1->Set(true);
	power2->Set(true);
	power3->Set(true);
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
	//VisionEvent *ve = 0;
	int ltState = 0;
	ForkSide side = DriverStation::GetInstance()->GetDigitalIn(1) ? Right : Left; //off = left fork, on = right fork
	//bool moveToDrop = false;
	switch(myState)
	{
		case TrackLine:
			if(e->type() == LineTracking) {
				ltState = static_cast<LineTrackingEvent*>(e)->state();
				DisplayWrapper::GetInstance()->PrintfLine(0,"Auto: Tracking Line.");
				DisplayWrapper::GetInstance()->PrintfLine(1,"Auto: LT: %i%i%i.",ltState|LeftFork,ltState|Forward,ltState|RightFork);
				DisplayWrapper::GetInstance()->Output();
				
				int sign = static_cast<int>(side);
				if(ltState == 0) {
					drive->Drive(0.5*sign,0,0);
				} else if(ltState == 1 && side == Left) {
					drive->Drive(0,0.5,0);
				} else if(ltState == 4 && side == Right) {
					drive->Drive(0,0.5,0);
				} else if(ltState == 7) {
					drive->Drive(0,0,0);
					myState = DropTube;
				} else {
					drive->Drive(-0.5*sign,0,0);
				}
			}
			break;
		/*case PlaceTube:
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
			break;*/
		case DropTube:
			Grabber::GetInstance()->pinch();
			Wait(1.0);
			drive->Drive(0,-0.4,0);
			myState = Done;
			break;
		default:
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
