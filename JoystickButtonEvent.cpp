#include "JoystickButtonEvent.h"

JoystickButtonEvent::JoystickButtonEvent(int button, EventListener* l)
{
	this->m_b = button;
	listen = l;
}

EventListener* JoystickButtonEvent::sender()
{
	return listen;
}

float JoystickButtonEvent::button()
{
	return m_b;
}
