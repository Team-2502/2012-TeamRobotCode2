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
		bool update() { return true; }
		void start();
		void stop();
		
	private:
		static void loop();
		static EventDispatcher *parent;
		Task *visionTask;
};

#endif
