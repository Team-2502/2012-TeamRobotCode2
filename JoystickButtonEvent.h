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

typedef enum ButtonLevel {
	sideFirstButton=3,
	middleFirstButton=4,
	loadingLevelButton=12,
	sideSecondButton=5,
	middleSecondButton=6
};

class JoystickButtonEvent : public Event
{
	public:
		JoystickButtonEvent(ButtonEvent button, EventListener* l);
		~JoystickButtonEvent() {}
		
		EventType type() { return JoystickButton; }
		EventListener* sender();
		ButtonEvent button();
		
	private:
		ButtonEvent m_b;
		EventListener *listen;
};

#endif
