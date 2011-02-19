#include "EncoderEvent.h"

EncoderEvent::EncoderEvent(float height, EventListener* l)
{
	m_height = height;
	listen = l;
}

EventListener* EncoderEvent::sender()
{
	return listen;
}

int EncoderEvent::height()
{
	return m_height;
}
