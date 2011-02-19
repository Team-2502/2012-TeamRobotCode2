#ifndef GYRO_LISTENER_H
#define GYRO_LISTENER_H

#include "EventListener.h"
#include "EventDispatcher.h"

class Gyro;

class GyroListener : public EventListener
{
	public:
		GyroListener(EventDispatcher* e);
		~GyroListener();
		void setParent(EventDispatcher *par) { parent = par; }
		bool update();
		
	private:
		Gyro* gyro;
		float lastAngle;
		EventDispatcher *parent;
};

#endif
