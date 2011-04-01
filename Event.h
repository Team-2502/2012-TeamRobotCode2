#ifndef EVENT_H
#define EVENT_H

enum EventType {
	NoEvent,
	JoystickPosition,
	GyroAngle,
	JoystickButton,
	TargetEvent,
	EncoderUpdate,
	LineTracking,
	GrabberEvent
};

class EventListener;

class Event
{
	public:
		virtual ~Event() {}
		virtual EventType type() { return NoEvent; }
		virtual EventListener* sender() = 0;
};

#endif
