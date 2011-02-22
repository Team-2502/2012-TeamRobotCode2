#include "JAGPidSource.h"

JagPIDSource::JagPIDSource(Jaguar* jag)
{
	this->jag = jag;
}

double JagPIDSource::PIDGet()
{
	return (double)jag->Get();
}
