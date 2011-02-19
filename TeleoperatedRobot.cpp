#include "TeleoperatedRobot.h"
#include "JoystickPositionEvent.h"
#include "JoystickButtonEvent.h"
#include "GyroAngleEvent.h"
#include "VisionEvent.h"
#include "RobotError.h"
#include "DisplayWrapper.h"
#include "EncoderEvent.h"
#include "config.h"

TeleoperatedRobot::TeleoperatedRobot(DriveType type)
{
	drive = new DriverWrapper(type);
	myError = RobotError::NoError();
	lastGyroReading = 0.0;
	servo = new Servo(DIGITAL_SIDECAR_PORT,SERVO_CHANNEL_START);
	servo->SetSafetyEnabled(false);
}

TeleoperatedRobot::~TeleoperatedRobot()
{
	delete drive; drive = 0;
	delete myError; myError = 0;
	delete servo; servo = 0;
}

bool TeleoperatedRobot::handle(Event *e)
{
	JoystickPositionEvent *jpe = 0;
	JoystickButtonEvent *jbe = 0;
	VisionEvent *ve = 0;
	ButtonEvent button;
	float vis_x = 0.0;
	float vis_y = 0.0;
	int encoderValue = 0;
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
				jpe->twist(),
				lastGyroReading);
		DisplayWrapper::GetInstance()->PrintfLine(0,"Gyro Angle: %f", lastGyroReading);
		DisplayWrapper::GetInstance()->Output();
		break;
	case GyroAngle:
		lastGyroReading = static_cast<GyroAngleEvent*>(e)->angle();
		break;
	case EncoderUpdate:
		encoderValue = static_cast<EncoderEvent*>(e)->height();
		DisplayWrapper::GetInstance()->PrintfLine(3,"Clicks: %f", encoderValue);
		DisplayWrapper::GetInstance()->Output();
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
		vis_x = static_cast<int>(ve->report().x);
		vis_y = static_cast<int>(ve->report().y);
		DisplayWrapper::GetInstance()->PrintfLine(1,"Target X: %i",vis_x);
		DisplayWrapper::GetInstance()->PrintfLine(2,"Target Y: %i",vis_y);
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
