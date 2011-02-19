#ifndef ENCODER_LISTENER_H
#define ENCODER_LISTENER_H

#include "EventListener.h"
#include "EventDispatcher.h"

class Enocoder;

class EncoderListener : public EventListener
{
	public:
		EncoderListener(EventDispatcher* e);
		~EncoderListener();
		void setParent(EventDispatcher *par) { parent = par; }
		bool update();
		
	private:
		Encoder* lift;
		float lastCount;
		EventDispatcher *parent;
};

#endif
