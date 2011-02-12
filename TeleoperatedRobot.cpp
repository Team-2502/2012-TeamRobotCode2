#include "TeleoperatedRobot.h"
#include "JoystickPositionEvent.h"
#include "JoystickButtonEvent.h"
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
	vector<ButtonEvent> buttons;
	bool ret = false;
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
		display->PrintfLine(1,"Joystick X: %f",jpe->x());
		display->PrintfLine(2,"Joystick Y: %f",jpe->y());
		display->PrintfLine(3,"Joystick T: %f",jpe->twist());
		display->Output();
		break;
	case GyroAngle:
		//lastGyroReading = static_cast<GyroAngleEvent*>(e)->angle();
		break;
	case JoystickButton:
		jbe = static_cast<JoystickButtonEvent*>(e);
		buttons = jbe->buttonEvents();
		for(unsigned int i = 0; i < buttons.size(); i++)
		{
			ButtonEvent ev = buttons[i];
			if(ev.button == 12 && ev.state) {
				servo->Set(1.0);
			} else if(ev.button == 11 && ev.state) {
				servo->Set(0.0);
			}
		}
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
