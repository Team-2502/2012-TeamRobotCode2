#include "TeleoperatedRobot.h"
#include "JoystickPositionEvent.h"
#include "JoystickButtonEvent.h"
#include "GyroAngleEvent.h"
#include "VisionEvent.h"
#include "RobotError.h"
#include "DisplayWrapper.h"
#include "EncoderEvent.h"
#include "LineEvent.h"
#include "Minibot.h"
#include "Grabber.h"
#include "Arm.h"
#include "config.h"

TeleoperatedRobot::TeleoperatedRobot(DriveType type)
{
	drive = new DriverWrapper(type);
	myError = RobotError::NoError();
	lastGyroReading = 0.0;
	gyroCorrection = 0.0;
	minibot = new Minibot;
	minibotTimer = new Timer;
	minibotTimer->Reset();

	//Power the line trackers.
	Solenoid* power1 = new Solenoid(7,1);
	Solenoid* power2 = new Solenoid(7,2);
	Solenoid* power3 = new Solenoid(7,3);
	power1->Set(true);
	power2->Set(true);
	power3->Set(true);
}

TeleoperatedRobot::~TeleoperatedRobot()
{
	delete drive; drive = 0;
	delete myError; myError = 0;
}

void TeleoperatedRobot::disable()
{
	drive->Drive(0,0,0);
	minibotTimer->Stop();
	minibotTimer->Reset();
}

bool TeleoperatedRobot::handle(Event *e)
{
	JoystickPositionEvent *jpe = 0;
	JoystickButtonEvent *jbe = 0;
	VisionEvent *ve = 0;
	LineTrackingEvent *lte = 0;
	ButtonEvent button;
	float vis_x = 0.0;
	float vis_y = 0.0;
	int encoderValue = 0;
	char l,r,c;
	l=r=c=' ';

	if(!e) {
		if(myError) { delete myError; myError = 0; }
		myError = new RobotError(Warning, "TeleoperatedRobot received null ptr.");
		return false;
	}
	switch(static_cast<int>(e->type()))
	{
	case JoystickPosition:
		jpe = static_cast<JoystickPositionEvent*>(e);
		drive->Drive(jpe->x(),
				jpe->y(),
				jpe->twist(), 0
		/*lastGyroReading+gyroCorrection*/);
		break;
	case GyroAngle:
		lastGyroReading = static_cast<GyroAngleEvent*>(e)->angle() + gyroCorrection;
		break;
	case EncoderUpdate:
		encoderValue = static_cast<EncoderEvent*>(e)->height();
		break;
	case JoystickButton:
		jbe = static_cast<JoystickButtonEvent*>(e);
		button = jbe->button();
		if(button.button == deployButton && button.state && minibotTimer->Get() > 114/*seconds*/) {
			minibot->Deploy();
		} else if(button.button == gyroResetButton && button.state) {
			//gyroCorrection = -1*lastGyroReading;
		} else if(button.button == 5 && button.state) {
			Arm::GetInstance()->setSpeed(0.75);
		} else if(button.button == 3 && button.state) {
			Arm::GetInstance()->setSpeed(-0.75);
		} else if(button.button == 5 && !button.state) {
			Arm::GetInstance()->setSpeed(0.0);
		} else if(button.button == 3 && !button.state) {
			Arm::GetInstance()->setSpeed(0.0);
		}
		
		if(button.button == 6 && button.state) {
			Grabber::GetInstance()->pinch();
		} else if(button.button == 4 && button.state) {
			Grabber::GetInstance()->expand();
		} else if(button.button == 6 && !button.state) {
			Grabber::GetInstance()->stop();
		} else if(button.button == 4 && !button.state) {
			Grabber::GetInstance()->stop();
		}
		break;
	case TargetEvent:
		ve = static_cast<VisionEvent*>(e);
		vis_x = static_cast<int>(ve->report().x);
		vis_y = static_cast<int>(ve->report().y);
		DisplayWrapper::GetInstance()->PrintfLine(1,"Target X: %i",vis_x);
		DisplayWrapper::GetInstance()->PrintfLine(2,"Target Y: %i",vis_y);
		DisplayWrapper::GetInstance()->Output();
		break;
	case LineTracking:
		lte = static_cast<LineTrackingEvent*>(e);
		l = (lte->state() & LeftFork)   ? 'L' : ' ';
		r = (lte->state() & RightFork)  ? 'R' : ' ';
		c = (lte->state() & Forward)    ? 'C' : ' ';
		DisplayWrapper::GetInstance()->PrintfLine(3,"Line State: %c%c%c",l,r,c);
		DisplayWrapper::GetInstance()->Output();
		break;
	default:
		if(myError) {
			delete myError; myError = 0;
			myError = new RobotError(Warning, "TeleoperatedRobot received unknown event.");
		}
		return false;
		break;
	}
	return true;
}

RobotError* TeleoperatedRobot::lastError()
{
	return myError;
}
