#ifndef ENCODER_EVENT_H
#define ENCODER_EVENT_H

#include "Event.h"

class EventListener;

class EncoderEvent : public Event
{
	public:
		EncoderEvent(float angle, EventListener* l);
		~EncoderEvent() {}
		
		EventType type() { return EncoderUpdate; }
		EventListener* sender();
		int height();
		
	private:
		float m_height;
		EventListener *listen;
};

#endif
