#ifndef LINE_LISTENER_H
#define LINE_LISTENER_H

#include "EventListener.h"
#include "LineEvent.h"
#include "EventDispatcher.h"

class LineListener : public EventListener
{
	public:
		LineListener(EventDispatcher *e);
		~LineListener();
		void setParent(EventDispatcher *par) { parent = par; }
		bool update();
		
	private:
		EventDispatcher *parent;
		DigitalInput* leftSensor;
		DigitalInput* rightSensor;
		DigitalInput* centerSensor;
		bool leftState,rightState,centerState;
};

#endif
