#include "WPILib.h"
#include "Robots.h"
#include "JoystickListener.h"
#include "RobotError.h"
#include "GyroListener.h"
#include "VisionListener.h"
#include "EncoderListener.h"
#include "config.h"

EventDispatcher::EventDispatcher(void)
{
	robot = new DisabledRobot();
}

void EventDispatcher::DisabledInit(void)
{
	if(robot)
		delete robot;
	robot = new DisabledRobot();
}

void EventDispatcher::AutonomousInit(void)
{
	if(robot)
		delete robot;
	robot = new AutonomousRobot();
	deleteAllListeners();
	visList = new VisionListener(this);
	listeners.push_back(new GyroListener(this));
	listeners.push_back(visList);
}

void EventDispatcher::AutonomousPeriodic()
{
	visList->update();
}

void EventDispatcher::AutonomousContinuous()
{
	static bool active = true;
	if(active) {
		for(unsigned int i = 0; i < listeners.size(); i++) { //Ask for events
			EventListener* listener = listeners[i];
			if(listener)
				listener->update();
		}
		for(unsigned int i = 0; i < events.size(); i++) { //Process events
			if(!robot->handle(events[i])) {
				RobotError* err = robot->lastError();
				if(err->getErrorLevel() == Fatal)
					active = false;
			}
			delete events[i]; //Clean up
			events[i] = 0;
		}
		events.clear();
	}
}

void EventDispatcher::TeleopInit(void)
{
	if(robot)
		delete robot;
	robot = new TeleoperatedRobot();
	deleteAllListeners();
	visList = new VisionListener(this);
	listeners.push_back(new JoystickListener(this, Extreme3DPro));
	listeners.push_back(new GyroListener(this));
	listeners.push_back(visList);
	listeners.push_back(new EncoderListener(this));
}

void EventDispatcher::TeleopPeriodic()
{
	visList->update();
}

void EventDispatcher::TeleopContinuous(void)
{
	static bool active = true;
	if(active) {
		for(unsigned int i = 0; i < listeners.size(); i++) { //Ask for events
			EventListener* listener = listeners[i];
			if(listener)
				listener->update();
		}
		for(unsigned int i = 0; i < events.size(); i++) { //Process events
			if(!robot->handle(events[i])) {
				RobotError* err = robot->lastError();
				if(err->getErrorLevel() == Fatal)
					active = false;
			}
			delete events[i]; //Clean up
			events[i] = 0;
		}
		events.clear();
	}
}

void EventDispatcher::deleteAllListeners()
{
	for(unsigned int i = 0; i < listeners.size(); i++) {
		delete listeners[i];
	}
	listeners.clear();
}

void EventDispatcher::sendEvent(Event *e)
{
	if(e)
		events.push_back(e);
}

START_ROBOT_CLASS(EventDispatcher);
