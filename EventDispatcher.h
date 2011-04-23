#ifndef EVENTDISPATCHER_H
#define EVENTDISPATCHER_H

#include "WPILib.h"
#include <vector>
using namespace std;

class Event;
class EventListener;
class VisionListener;
class RobotMode;
class TeleoperatedRobot;
class DisabledRobot;
class AutonomousRobot;

class EventDispatcher : public IterativeRobot
{
public:
	EventDispatcher(void);

	void RobotInit(void) {}

	void DisabledInit(void);
	void DisabledPeriodic(void) {}
	void DisabledContinuous(void) {}

	void AutonomousInit(void);
	void AutonomousPeriodic(void) {}
	void AutonomousContinuous(void);

	void TeleopInit(void);
	void TeleopPeriodic(void) {}
	void TeleopContinuous(void);
	
	void deleteAllListeners();
	void sendEvent(Event *e);

private:
	void callSafetyFunctions();
	
	RobotMode *robot;
	AutonomousRobot *autoBot; //lol
	TeleoperatedRobot *teleBot; //decepticon?
	DisabledRobot *crippleBot;
	VisionListener* visList;
	vector<EventListener*> listeners;
	vector<Event*> events;
};

#endif
