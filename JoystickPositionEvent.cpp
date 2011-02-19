#include "JoystickPositionEvent.h"

JoystickPositionEvent::JoystickPositionEvent(float x, float y, float twist, EventListener* l)
{
	this->m_x = x;
	this->m_y = y;
	this->m_twist = twist;
	listen = l;
}

EventListener* JoystickPositionEvent::sender()
{
	return listen;
}

float JoystickPositionEvent::x()
{
	return m_x;
}

float JoystickPositionEvent::y()
{
	return m_y;
}

float JoystickPositionEvent::twist()
{
	return m_twist;
}
