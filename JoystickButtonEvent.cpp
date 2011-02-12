#include "JoystickButtonEvent.h"

JoystickButtonEvent::JoystickButtonEvent(vector<ButtonEvent> button, EventListener* l)
{
	this->m_b = button;
	listen = l;
}

EventListener* JoystickButtonEvent::sender()
{
	return listen;
}

vector<ButtonEvent> JoystickButtonEvent::buttonEvents()
{
	return m_b;
}

bool JoystickButtonEvent::compareButtonEvents(vector<ButtonEvent> first, vector<ButtonEvent> second)
{
	if(first.size() != second.size())
		return false;
	for(int i = 0; i < first.size(); i++)
	{
		ButtonEvent one = first[i];
		ButtonEvent two = second[i];
		if(one.state != two.state)
			return false;
	}
	return true;
}
