#include "WPILib.h"
#include "Robots.h"
#include "JoystickListener.h"
#include "RobotError.h"
#include "GyroListener.h"
#include "VisionListener.h"
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
	//robot = new AutonomousRobot();
	robot = new DisabledRobot();
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
}

void EventDispatcher::TeleopPeriodic()
{
	visList->update();
}

void EventDispatcher::TeleopContinuous(void)
{
	static bool active = true;
	if(active) {
		for(unsigned int i = 0; i < listeners.size(); i++) {
			EventListener* listener = listeners[i];
			listener->update();
		}
		for(unsigned int i = 0; i < events.size(); i++) {
			if(!robot->handle(events[i])) {
				RobotError* err = robot->lastError();
				if(err->getErrorLevel() == Fatal)
					active = false;
			}
			delete events[i];
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
	events.push_back(e);
}

START_ROBOT_CLASS(EventDispatcher);
