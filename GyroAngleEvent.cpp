#include "GyroAngleEvent.h"

GyroAngleEvent::GyroAngleEvent(float angle, EventListener* l)
{
	m_angle = angle;
	listen = l;
}

EventListener* GyroAngleEvent::sender()
{
	return listen;
}

float GyroAngleEvent::button()
{
	return m_angle;
}
