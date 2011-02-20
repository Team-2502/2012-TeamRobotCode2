#include "EncoderListener.h"
#include "EncoderEvent.h"
#include "WPILib.h"
#include "config.h"

EncoderListener::EncoderListener(EventDispatcher *e)
{
	parent = e;
	lift = new Encoder(ARM_CHAIN_ENCODER_A_CHANNEL, ARM_CHAIN_ENCODER_B_CHANNEL);
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
