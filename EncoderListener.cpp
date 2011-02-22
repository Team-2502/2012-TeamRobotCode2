#include "EncoderListener.h"
#include "EncoderEvent.h"
#include "WPILib.h"
#include "config.h"

EncoderListener::EncoderListener(EventDispatcher *e, int chanA, int chanB)
{
	parent = e;
	lift = new Encoder(cA = chanA, cB = chanB);
	lastCount = lift->Get();
}

EncoderListener::~EncoderListener()
{
	delete lift;
}

bool EncoderListener::update()
{
	if(lift->Get() != lastCount)
	{
		lastCount = lift->Get();
		parent->sendEvent(new EncoderEvent(lastCount,this));
	}
	return true;
}
