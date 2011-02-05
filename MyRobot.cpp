#include <math.h>

#include <Dashboard.h>
#include <WPILib.h>

#include "DisplayWrapper.h"
#include "DriverWrapper.h"
#include "JoystickWrapper.h"

class BetaRobot : public IterativeRobot
{
	public:
		BetaRobot(void)
		{
			joystick = new JoystickWrapper(1, Extreme3DPro);
			joystick->SetSnapPoints(4);
			driver = new DriverWrapper(Mecanum, 7, 2, 3, 1);
			driver->GetRobotDrive()->SetSafetyEnabled(false);
			display = new DisplayWrapper();
		}
	
		void RobotInit(void) {}
		void DisabledInit(void) {}
		void AutonomousInit(void) {}
		void TeleopInit(void) {}
		
		void AutonomousPeriodic(void) 
		{
		}
		
		void TeleopPeriodic(void)
		{
			float x, y;
			joystick->GetRawAxis(&x, &y);
			display->PrintfLine(0, "Joystick Angle:     %f", joystick->GetAngle());
			display->PrintfLine(1, "Joystick Throttle:  %f", joystick->GetThrottle());
			display->PrintfLine(2, "Joystick X:         %f", x);
			display->PrintfLine(3, "Joystick Y:         %f", y);
			display->PrintfLine(4, "Joystick Magnitude: %f", joystick->GetMagnitude());
			display->PrintfLine(5, "Joystick Rotation:  %f", joystick->GetRotation());
			joystick->GetPov(&x, &y);
			display->PrintfLine(6, "Joystick POV X:     %f", x);
			display->PrintfLine(7, "Joystick POV Y:     %f", y);
			float t = -1.0 * joystick->GetThrottle();
			display->SetScrollLocation(t);
			display->Output();
			driver->Drive(x, y, joystick->GetRotation());
		}
		
		/** Unused functions */
		void DisabledPeriodic(void) {}
		void DisabledContinuous(void) {}
		void AutonomousContinuous(void) {}
		void TeleopContinuous(void) {}
		
	private:
		DisplayWrapper* display;
		DriverWrapper* driver;
		JoystickWrapper* joystick;
};

START_ROBOT_CLASS(BetaRobot);
