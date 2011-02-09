#include "JoystickListener.h"
#include "JoystickEvents.h"

JoystickListener::JoystickListener(StickType type)
{
	stick = new JoystickWrapper(type);
}

JoystickListener::~JoystickListener()
{
	delete stick;
}

Event* JoystickListener::getEvent(int index)
{
	Event* ret = 0;
	float x,y;
	switch(index)
	{
		case 0: //Position
			stick->GetAxis(&x,&y);
			ret = new JoystickPositionEvent(x,y,stick->GetRotation());
			break;
		case 1: //Button
			break;
		default:
			break;
	}
	return ret;
}