#ifndef JOYSTICK_LISTENER_H
#define JOYSTICK_LISTENER_H

#include "EventListener.h"
#include "JoystickWrapper.h"

class JoystickListener : public EventListener
{
	public:
		JoystickListener(StickType type = Extreme3DPro);
		~JoystickListener();
		Event* getEvent(int index);
		
		int getMessageQuantity() { return 2; }
		
	private:
		JoystickWrapper *stick;
};

#endif
