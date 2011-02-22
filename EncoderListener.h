#ifndef ENCODER_LISTENER_H
#define ENCODER_LISTENER_H

#include "EventListener.h"
#include "EventDispatcher.h"

class Encoder;

class EncoderListener : public EventListener
{
	public:
		EncoderListener(EventDispatcher* e, int chanA, int chanB);
		~EncoderListener();
		void setParent(EventDispatcher *par) { parent = par; }
		bool update();
		int getAChannel() { return cA; }
		int getBChannel() { return cB; }
		
	private:
		Encoder* lift;
		int lastCount;
		int cA,cB;
		EventDispatcher *parent;
};

#endif
