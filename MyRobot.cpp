#include "WPILib.h"
#include "Robots.h"
#include "config.h"

class EventDispatcher : public IterativeRobot
{
	public:
		EventDispatcher(void)
		{
			robot = new DisabledRobot();
			joystickListener = new JoystickListener(Extreme3DPro); //has default port
#ifdef USE_GYRO
			gyroListener = new GyroListener(); //has default port
#endif
		}
	
		void RobotInit(void) {}
		
		void DisabledInit(void)
		{
			robot = new DisabledRobot();
		}
		void DisabledPeriodic(void) {}
		void DisabledContinuous(void) {}
		
		void AutonomousInit(void)
		{
			robot = new AutonomousRobot();
		}
		void AutonomousPeriodic(void) {}
		void AutonomousContinuous(void) {}
		
		void TeleopInit(void)
		{
			robot = new TeleoperatedRobot();
		}
		void TeleopPeriodic(void) {}
		void TeleopContinuous(void)
		{
#ifdef USE_GYRO
			robot->handle(gyroListener->getEvent());
#endif
			robot->handle(joytickListener->getPositionEvent());
			robot->handle(joytickListener->getButtonEvent());
		}
		
	private:
		RobotMode *robot;
		JoystickListener *joystickListener;
#ifdef USE_GYRO
		GyroListener *gyroListener;
#endif
};

START_ROBOT_CLASS(EventDispatcher);
