#ifndef GYRO_ANGLE_EVENT_H
#define GYRO_ANGLE_EVENT_H

#include "Event.h"

class EventListener;

class GyroAngleEvent : public Event
{
	public:
		GyroAngleEvent(float angle, EventListener* l);
		~GyroAngleEvent() {}
		
		EventType type() { return GyroAngle; }
		EventListener* sender();
		float angle();
		
	private:
		float m_angle;
		EventListener *listen;
};

#endif
