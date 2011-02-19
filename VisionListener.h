#ifndef VISION_LISTENER_H
#define VISION_LISTENER_H

#include "EventListener.h"
#include "EventDispatcher.h"
#include "VisionRoutines.h"

class VisionListener : public EventListener
{
	public:
		VisionListener(EventDispatcher* e);
		~VisionListener();
		void setParent(EventDispatcher *par) { parent = par; }
		bool update();
		
	private:
		TargetReport lastReport;
		EventDispatcher *parent;
		Vision *vis;
};

#endif
