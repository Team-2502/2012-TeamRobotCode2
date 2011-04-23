#include "Grabber.h"
#include "config.h"

Grabber* Grabber::instance = NULL;

Grabber* Grabber::GetInstance()
{
	if(!instance) {
		instance = new Grabber;
	}
	return instance;
}

Grabber::Grabber()
{
	GrabberVicT = new Victor(TOP_GRABBER_CHANNEL);
	GrabberVicB = new Victor(BOTTOM_GRABBER_CHANNEL);
	GrabberVicT->SetSafetyEnabled(false);
	GrabberVicB->SetSafetyEnabled(false);
	topStopperL = new DigitalInput(TOP_STOPPER_PORT_L);
	topStopperR = new DigitalInput(TOP_STOPPER_PORT_R);
	bottomStopperL = new DigitalInput(BOTTOM_STOPPER_PORT_L);
	bottomStopperR = new DigitalInput(BOTTOM_STOPPER_PORT_R);
}

Grabber::~Grabber()
{
	delete GrabberVicT;
	delete GrabberVicB;
	instance = NULL;
}

void Grabber::enforceSafetyHack()
{
	safeSetSpeed(Top,GrabberVicT->Get());
	safeSetSpeed(Bottom,GrabberVicB->Get());
}

void Grabber::safeSetSpeed(Rail r, float speed)
{
	if(r == Top) { //Good
		if(speed > 0 && !topStopperL->Get())
			GrabberVicT->Set(speed);
		else if(speed < 0 && !topStopperR->Get())
			GrabberVicT->Set(speed);
		else
			GrabberVicT->Set(0.0);
	} else if(r == Bottom) {
		if(speed > 0 && !bottomStopperR->Get())
			GrabberVicB->Set(speed);
		else if(speed < 0 && !bottomStopperL->Get())
			GrabberVicB->Set(speed);
		else
			GrabberVicB->Set(0.0);
	}
}

//Moves top to left.
void Grabber::pinch()
{
	safeSetSpeed(Top,0.5);
	safeSetSpeed(Bottom,-0.5);
}

void Grabber::shiftLeft()
{
	GrabberVicT->SetSpeed(0.5);
	GrabberVicB->SetSpeed(0.5);
}

void Grabber::shiftRight()
{
	GrabberVicT->SetSpeed(-0.5);
	GrabberVicB->SetSpeed(-0.5);
}

//Moves top to right.
void Grabber::expand()
{
	safeSetSpeed(Top,-0.5);
	safeSetSpeed(Bottom,0.5);
}

void Grabber::stop()
{
	GrabberVicT->Set(0.0);
	GrabberVicB->Set(0.0);
}
