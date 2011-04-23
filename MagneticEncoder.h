#ifndef MAGNETIC_ENCODER
#define MAGNETIC_ENCODER

#include "WPILib.h"
#include "config.h"
#include "EventDispatcher.h"
#include "EventListener.h"

class MagneticEncoder : public EventListener
{
	public:
		MagneticEncoder(EventDispatcher *e);
		~MagneticEncoder();
		
		bool update() {return true;}
		void setParent(EventDispatcher *e) { parent = e; }
		
	private:
		static AnalogChannel *channelTop;
		static AnalogChannel *channelBottom;
		
		Task *updatingTask;
		static EventDispatcher *parent;
		static void calculate(); //runs in loop.
};

#endif
