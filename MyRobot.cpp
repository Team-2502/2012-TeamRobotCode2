#include "WPILib.h"
#include "Robots.h"
#include "JoystickListener.h"
#include "config.h"

class EventDispatcher : public IterativeRobot
{
	public:
		EventDispatcher(void)
		{
			robot = new DisabledRobot();
			//listeners.push_back(new GyroListener());
		}
		
		void RobotInit(void) {}
		
		void DisabledInit(void)
		{
			if(robot)
				delete robot;
			robot = new DisabledRobot();
		}
		void DisabledPeriodic(void) {}
		void DisabledContinuous(void) {}
		
		void AutonomousInit(void)
		{
			if(robot)
				delete robot;
			//robot = new AutonomousRobot();
			robot = new DisabledRobot();
		}
		void AutonomousPeriodic(void) {}
		void AutonomousContinuous(void) {}
		
		void TeleopInit(void)
		{
			if(robot)
				delete robot;
			robot = new TeleoperatedRobot();
			deleteAllListeners();
			listeners.push_back(new JoystickListener(Extreme3DPro));
		}
		void TeleopPeriodic(void) {}
		void TeleopContinuous(void)
		{
			static bool active = true;
			if(active)
			{
				for(unsigned int j = 0; j < listeners.size(); j++) {
					EventListener* listener = listeners[j];
					for(int i = 0; i < listener->getMessageQuantity(); i++) {
						if(!robot->handle(listener->getEvent(i)))
						{
							RobotError* err = robot->lastError();
							if(err->getErrorLevel() == Fatal)
								active = false;
						}
					}
				}
			}
		}
		
		void deleteAllListeners()
		{
			for(unsigned int i = 0; i < listeners.size(); i++) {
				delete listeners[i];
			}
			listeners.clear();
		}
		
	private:
		RobotMode *robot;
		vector<EventListener*> listeners;
};

START_ROBOT_CLASS(EventDispatcher);
