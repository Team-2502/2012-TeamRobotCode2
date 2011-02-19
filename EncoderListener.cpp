#include "EncoderListener.h"
#include "GyroAngleEvent.h"
#include "WPILib.h"
#include "config.h"

EncoderListener::EncoderListener(EventDispatcher *e)
{
	parent = e;
	lift = new Encoder(ARM_CHAIN_ENCODER_A_CHANNEL, ARM_CHAIN_ENCODER_B_CHANNEL);;
	lastCount = lift->Get();
}

EncoderListener::~EncoderListener()
{
	delete lift;
}

bool EncoderListener::update()
{
	lastCount = lift->Get();
	return true;
}
