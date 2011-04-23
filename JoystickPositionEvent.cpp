#include "JoystickPositionEvent.h"

JoystickPositionEvent::JoystickPositionEvent(float x, float y, float twist, float throttle, EventListener* l)
{
	this->m_x = x;
	this->m_y = y;
	this->m_twist = twist;
	this->m_throttle = throttle;
	listen = l;
}

EventListener* JoystickPositionEvent::sender()
{
	return listen;
}

float JoystickPositionEvent::x() const
{
	return m_x;
}

float JoystickPositionEvent::y() const
{
	return m_y;
}

float JoystickPositionEvent::twist() const
{
	return m_twist;
}

float JoystickPositionEvent::throttle() const
{
	return m_throttle;
}
