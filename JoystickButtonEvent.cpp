#include "JoystickButtonEvent.h"

JoystickButtonEvent::JoystickButtonEvent(ButtonEvent button, EventListener* l)
{
	this->m_b = button;
	listen = l;
}

EventListener* JoystickButtonEvent::sender()
{
	return listen;
}

ButtonEvent JoystickButtonEvent::button()
{
	return m_b;
}
