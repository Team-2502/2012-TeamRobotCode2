#include "WPILib.h"
#include "Robots.h"
#include "JoystickListener.h"
#include "RobotError.h"
#include "GyroListener.h"
#include "VisionListener.h"
#include "EncoderListener.h"
#include "MagneticEncoder.h"
#include "LineListener.h"
#include "DisplayWrapper.h"
#include "Grabber.h"
#include "config.h"

EventDispatcher::EventDispatcher(void)
{
	crippleBot = new DisabledRobot();
	teleBot = new TeleoperatedRobot();
	autoBot = new AutonomousRobot();
	robot = crippleBot;
	
	Solenoid* power1 = new Solenoid(8,1);
	Solenoid* power2 = new Solenoid(8,2);
	Solenoid* power3 = new Solenoid(8,3);
	power1->Set(true);
	power2->Set(true);
	power3->Set(true);
	
	visList = new VisionListener(this);
	listeners.push_back(new GyroListener(this));
	listeners.push_back(new JoystickListener(this, Extreme3DPro));
	listeners.push_back(new EncoderListener(this,ARM_CHAIN_ENCODER_A_CHANNEL, ARM_CHAIN_ENCODER_B_CHANNEL));
	//listeners.push_back(new MagneticEncoder(this));
	listeners.push_back(new LineListener(this));
	listeners.push_back(visList);
}

void EventDispatcher::DisabledInit(void)
{
	robot = crippleBot;
	teleBot->disable();
	autoBot->disable();
}

void EventDispatcher::AutonomousInit(void)
{
	#ifdef USE_AUTONOMOUS
	robot = autoBot;
	#else
	robot = crippleBot;
	#endif
	visList->start();
	teleBot->disable();
}

void EventDispatcher::AutonomousContinuous()
{
	static bool active = true;
	if(active) {
		callSafetyFunctions();
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
	robot = teleBot;
	visList->start();
	autoBot->disable();
}

void EventDispatcher::TeleopContinuous(void)
{
	static bool active = true;
	if(active) {
		callSafetyFunctions();
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
	if(e) {
		events.push_back(e);
		switch(e->type()) {
			case JoystickPosition:
				DisplayWrapper::GetInstance()->PrintfLine(2,"Event: JoyPos");
				break;
			case GyroAngle:
				DisplayWrapper::GetInstance()->PrintfLine(2,"Event: Gyro");
				break;
			case JoystickButton:
				DisplayWrapper::GetInstance()->PrintfLine(2,"Event: JoyBtn");
				break;
			case TargetEvent:
				DisplayWrapper::GetInstance()->PrintfLine(2,"Event: Vision");
				break;
			case EncoderUpdate:
				DisplayWrapper::GetInstance()->PrintfLine(2,"Event: Encodr");
				break;
			case LineTracking:
				DisplayWrapper::GetInstance()->PrintfLine(3,"Event: LineTr");
				break;
			default:
				DisplayWrapper::GetInstance()->PrintfLine(2,"Event: Unknown");
				break;
		}
		DisplayWrapper::GetInstance()->Output();
	}
}

void EventDispatcher::callSafetyFunctions()
{
	Grabber::GetInstance()->enforceSafetyHack();
}

START_ROBOT_CLASS(EventDispatcher);
