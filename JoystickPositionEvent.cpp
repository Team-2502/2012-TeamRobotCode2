#include "JoystickPositionEvent.h"

JoystickPositionEvent::JoystickPositionEvent(float x, float y, float twist, EventListener* l)
{
	this->x = x;
	this->y = y;
	this->twist = twist;
	listen = l;
}


EventListener* JoystickPositionEvent::sender()
{
	return listen;
}

float JoystickPositionEvent::x()
{
	return x;
}

float JoystickPositionEvent::y()
{
	return y;
}

float JoystickPositionEvent::twist()
{
	return twist;
}
