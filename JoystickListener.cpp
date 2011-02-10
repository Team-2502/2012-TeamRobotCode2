#include "JoystickListener.h"
#include "JoystickPositionEvent.h"
#include "config.h"

JoystickListener::JoystickListener(StickType type)
{
	stick = new JoystickWrapper(JOYSTICK_PORT,type); //check
}

JoystickListener::~JoystickListener()
{
	delete stick; stick = 0;
}

Event* JoystickListener::getEvent(int index)
{
	Event* ret = 0;
	float x,y;
	switch(index)
	{
		case 0: //Position
			stick->GetAxis(&x,&y);
			ret = new JoystickPositionEvent(x,y,stick->GetRotation(), this);
			break;
		case 1: //Button
			break;
		default:
			break;
	}
	return ret;
}
