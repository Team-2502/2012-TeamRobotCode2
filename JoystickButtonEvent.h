#ifndef JOYSTICK_BUTTON_EVENT_H
#define JOYSTICK_BUTTON_EVENT_H

#include "Event.h"
#include <vector>
using namespace std;

class EventListener;

struct ButtonEvent {
	int button;
	bool state;
};

class JoystickButtonEvent : public Event
{
	public:
		JoystickButtonEvent(vector<ButtonEvent> button, EventListener* l);
		~JoystickButtonEvent() {}
		
		EventType type() { return JoystickButton; }
		EventListener* sender();
		vector<ButtonEvent> buttonEvents();
		
	private:
		vector<ButtonEvent> m_b;
		EventListener *listen;
};

#endif
