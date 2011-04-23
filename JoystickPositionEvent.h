#ifndef JOYSTICK_POSITION_EVENT_H
#define JOYSTICK_POSITION_EVENT_H

#include "Event.h"

class EventListener;

class JoystickPositionEvent : public Event
{
	public:
		JoystickPositionEvent(float x, float y, float twist, float throttle, EventListener* l);
		~JoystickPositionEvent() {}
		
		EventType type() { return JoystickPosition; }
		EventListener* sender();
		float x() const;
		float y() const;
		float twist() const;
		float throttle() const;
		
	private:
		float m_x,m_y,m_twist,m_throttle;
		EventListener *listen;
};

#endif
