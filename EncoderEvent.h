#ifndef ENCODER_EVENT_H
#define ENCODER_EVENT_H

#include "Event.h"

class EventListener;

class EncoderEvent : public Event
{
	public:
		EncoderEvent(int angle, EventListener* l);
		~EncoderEvent() {}
		
		EventType type() { return EncoderUpdate; }
		EventListener* sender();
		int height();
		
	private:
		int m_height;
		EventListener *listen;
};

#endif
