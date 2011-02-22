#ifndef JAGPIDSOURCE_H
#define JAGPIDSOURCE_H

#include "WPILib.h"

class JagPIDSource : public PIDSource
{
	public:
		JagPIDSource(Jaguar* jag);
		double PIDGet();
		
	private:
		Jaguar* jag;
};

#endif
