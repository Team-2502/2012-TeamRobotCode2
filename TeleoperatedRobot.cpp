#include "TeleoperatedRobot.h"
#include "JoystickPositionEvent.h"
#include "JoystickButtonEvent.h"
#include "GyroAngleEvent.h"
#include "VisionEvent.h"
#include "RobotError.h"
#include "config.h"

TeleoperatedRobot::TeleoperatedRobot(DriveType type)
{
	drive = new DriverWrapper(type);
	myError = RobotError::NoError();
	display = new DisplayWrapper;
	lastGyroReading = 0.0;
	servo = new Servo(DIGITAL_SIDECAR_PORT,SERVO_CHANNEL);
	servo->SetSafetyEnabled(false);
}

TeleoperatedRobot::~TeleoperatedRobot()
{
	delete drive; drive = 0;
	delete myError; myError = 0;
	delete display; display = 0;
}

bool TeleoperatedRobot::handle(Event *e)
{
	JoystickPositionEvent *jpe = 0;
	JoystickButtonEvent *jbe = 0;
	VisionEvent *ve = 0;
	ButtonEvent button;
	bool ret = false;
	int region = -1;
	if(!e) {
		if(myError) delete myError;
		myError = new RobotError(Warning, "TeleoperatedRobot received null ptr.");
		return false;
	}
	switch(static_cast<int>(e->type()))
	{
	case JoystickPosition:
		jpe = static_cast<JoystickPositionEvent*>(e);
		drive->Drive(jpe->x(),
				jpe->y(),
				jpe->twist(),
				lastGyroReading);
		display->PrintfLine(0,"Gyro Angle: %f", lastGyroReading);
		display->Output();
		break;
	case GyroAngle:
		lastGyroReading = static_cast<GyroAngleEvent*>(e)->angle();
		break;
	case JoystickButton:
		jbe = static_cast<JoystickButtonEvent*>(e);
		button = jbe->button();
		if(button.button == 11 && button.state) {
			servo->Set(1.0);
		}
		else if(button.button == 12 && button.state) {
			servo->Set(0.0);
		}
		break;
	case TargetEvent:
		ve = static_cast<VisionEvent*>(e);
		region = static_cast<int>(ve->report().region);
		display->PrintfLine(1,"Region: %i",region);
		break;
	default:
		if(myError) {
			delete myError; myError = 0;
			myError = new RobotError(Warning, "TeleoperatedRobot received unknown event.");
		}
		break;
	}
	return ret;
}

RobotError* TeleoperatedRobot::lastError()
{
	return myError;
}
