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
	GrabberJag1 = new Jaguar(5);
	GrabberJag2 = new Jaguar(6);
	GrabberJag1->SetSafetyEnabled(false);
	GrabberJag2->SetSafetyEnabled(false);
}

Grabber::~Grabber()
{
	delete GrabberJag1;
	delete GrabberJag2;
	instance = NULL;
}

void Grabber::pinch()
{
	GrabberJag1->Set(0.5);
	GrabberJag2->Set(-0.5);
}

void Grabber::expand()
{
	GrabberJag1->Set(-0.5);
	GrabberJag2->Set(0.5);
}

void Grabber::stop()
{
	GrabberJag1->Set(0.0);
	GrabberJag2->Set(0.0);
}
