#ifndef JOYSTICK_LISTENER_H
#define JOYSTICK_LISTENER_H

#include "EventListener.h"
#include "JoystickWrapper.h"
#include "JoystickButtonEvent.h"
#include "EventDispatcher.h"

class JoystickListener : public EventListener
{
	public:
		JoystickListener(EventDispatcher* e, StickType type = Extreme3DPro);
		~JoystickListener();
		void setParent(EventDispatcher *par) { parent = par; }
		bool update();
		
	private:
		vector<ButtonEvent> getButtonStates();
		JoystickWrapper *stick;
		vector<ButtonEvent> lastButtonStates;
		EventDispatcher *parent;
};

#endif
