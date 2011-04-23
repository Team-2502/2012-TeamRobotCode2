#ifndef GRABBER_H
#define GRABBER_H

#include "WPILib.h"

class Grabber
{
	public:
		static Grabber* GetInstance();
		~Grabber();
		void pinch();
		void expand();
		void stop();
		void enforceSafetyHack(); //Hack.
		void shiftLeft();
		void shiftRight();
		
	private:
		enum Rail { Top, Bottom };
		Grabber();
		void safeSetSpeed(Rail r, float speed);
		Victor* GrabberVicT;
		Victor* GrabberVicB;
		DigitalInput *topStopperL;
		DigitalInput *topStopperR;
		DigitalInput *bottomStopperL;
		DigitalInput *bottomStopperR;
		static Grabber* instance;
};

#endif // Grabber
