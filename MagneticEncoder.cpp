#include <math.h>
#include "MagneticEncoder.h"
#include "GrabberPositionEvent.h"

#define METERS_PER_REVOLUTION 0

EventDispatcher* MagneticEncoder::parent = NULL;
AnalogChannel* MagneticEncoder::channelTop = NULL;
AnalogChannel* MagneticEncoder::channelBottom = NULL;

MagneticEncoder::MagneticEncoder(EventDispatcher* e)
{
	if(!parent)
		parent = e;
	channelTop    = new AnalogChannel(ANALOG_SLOT,    MAGNETIC_ENCODER_TOP_CHANNEL);
	channelBottom = new AnalogChannel(ANALOG_SLOT, MAGNETIC_ENCODER_BOTTOM_CHANNEL);
	updatingTask = new Task("2502Mg",(FUNCPTR)calculate);
	updatingTask->Start();
}

MagneticEncoder::~MagneticEncoder()
{
	updatingTask->Stop();
	delete updatingTask;
	delete channelTop;
	delete channelBottom;
}

double d_abs(double value)
{
	if(value < 0)
		return -1*value;
	return value;
}

void MagneticEncoder::calculate()
{
	double lastReadValueTop = 0;
	double lastReadValueBottom = 0;
	int revolutionsTop = 0;
	int revolutionsBottom = 0;
	int direction = 1; //1 = forward, -1 = backward
	while(true) {
		if(d_abs(lastReadValueTop - channelTop->GetVoltage()) > 0.75) { //If there's a discontinuity
			direction = (0.5 - channelTop->GetVoltage() > 0) ? 1 : -1; //Depends on whether it jumped up or down.
			revolutionsTop += direction;
			parent->sendEvent(new GrabberPositionEvent(double(METERS_PER_REVOLUTION)*revolutionsTop,0));
		}
		if(d_abs(lastReadValueBottom - channelBottom->GetVoltage()) > 0.75) { //If there's a discontinuity
			direction = (0.5 - channelBottom->GetVoltage() > 0) ? 1 : -1;
			revolutionsBottom += direction;
			parent->sendEvent(new GrabberPositionEvent(double(METERS_PER_REVOLUTION)*revolutionsBottom,0));
		}
		lastReadValueTop = channelTop->GetVoltage();
		lastReadValueBottom = channelBottom->GetVoltage();
	}
}
