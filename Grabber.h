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
		
	private:
		Grabber();
		Jaguar* GrabberJag1;
		Jaguar* GrabberJag2;
		static Grabber* instance;
};

#endif // Grabber
