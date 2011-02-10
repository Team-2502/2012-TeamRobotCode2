#ifndef EVENT_H
#define EVENT_H

enum EventType {
	None,
	JoystickPosition,
	GyroAngle
};

class EventListener;

class Event
{
	public:
		virtual ~Event() {}
		virtual EventType type() { return None; }
		EventListener* sender() = 0;
};

#endif
