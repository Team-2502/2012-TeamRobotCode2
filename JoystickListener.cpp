#include "JoystickListener.h"
#include "JoystickPositionEvent.h"
#include "JoystickButtonEvent.h"
#include "config.h"

JoystickListener::JoystickListener(EventDispatcher* e, StickType type)
{
	parent = e;
	stick = new JoystickWrapper(JOYSTICK_PORT,type); //check
	lastButtonStates = getButtonStates();
}

JoystickListener::~JoystickListener()
{
	delete stick; stick = 0;
}

bool JoystickListener::update()
{
	float x,y;
	stick->GetRawAxis(&x,&y);
	parent->sendEvent(new JoystickPositionEvent(x,y,stick->GetRotation(), this));
	for(int i = 1; i <= 12; i++)
	{
		if(stick->GetJoystick()->GetRawButton(i) != lastButtonStates[i-1].state) {
			ButtonEvent be;
			be.button = i;
			be.state = stick->GetJoystick()->GetRawButton(i);
			lastButtonStates[i-1] = be;
			parent->sendEvent(new JoystickButtonEvent(be,this));
		}
	}
	return true;
}

vector<ButtonEvent> JoystickListener::getButtonStates()
{
	vector<ButtonEvent> ret;
	Joystick* js = stick->GetJoystick();
	for(int i = 1; i <= 12; i++)
	{
		ButtonEvent be;
		be.button = i;
		be.state = js->GetRawButton(i);
		ret.push_back(be);
	}
	return ret;
}

