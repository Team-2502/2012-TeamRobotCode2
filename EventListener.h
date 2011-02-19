#ifndef EVENTLISTENER_H
#define EVENTLISTENER_H

class Event;
class EventDispatcher;

class EventListener
{
	public:
		virtual ~EventListener() {}
		virtual bool update() = 0;
		virtual void setParent(EventDispatcher *) = 0;
};

#endif
