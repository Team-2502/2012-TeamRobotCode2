#include "JoystickListener.h"
#include "JoystickPositionEvent.h"
#include "JoystickButtonEvent.h"
#include "config.h"

JoystickListener::JoystickListener(StickType type)
{
	stick = new JoystickWrapper(JOYSTICK_PORT,type); //check
	lastButtonStates = getButtonStates();
}

JoystickListener::~JoystickListener()
{
	delete stick; stick = 0;
}

vector<ButtonEvent> JoystickListener::getButtonStates()
{
	vector<ButtonEvent> ret;
	Joystick* js = stick->GetJoystick();
	for(int i = 1; i <= 12; i++)
	{
		ret.push_back({i,js->GetRawButton(i)});
	}
	return ret;
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
			if(lastButtonStates != getButtonStates())
			{
				lastButtonStates = getButtonStates();
				ret = new JoystickButtonEvent(lastButtonStates, this);
			}
			break;
		default:
			break;
	}
	return ret;
}
