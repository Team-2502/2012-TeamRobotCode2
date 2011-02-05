#include <math.h>

#include <Dashboard.h>
#include <WPILib.h>

#include "DisplayWrapper.h"
#include "DriverWrapper.h"
#include "JoystickWrapper.h"
<<<<<<< HEAD
#include "VisionRoutines.h"
=======
>>>>>>> c0cc8be37dc7ea7c4bbbdc524ac8a1082b3629c4

class BetaRobot : public IterativeRobot
{
	public:
		BetaRobot(void)
		{
			joystick = new JoystickWrapper(1, Extreme3DPro);
			joystick->SetSnapPoints(4);
<<<<<<< HEAD
			display = new DisplayWrapper;
			vis = Vision::GetInstance();
		}
		
		void RobotInit(void) {/*pSystem->start();*/}
		void DisabledInit(void) {/*pSystem->stop();*/}
		void AutonomousInit(void) {/*pSystem->setCompressor(true);*/}
		void TeleopInit(void) {/*pSystem->start();*/}
		
		void AutonomousPeriodic(void) {display->PrintfLine(8, "We're in autonomous mode!");}
=======
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
		
>>>>>>> c0cc8be37dc7ea7c4bbbdc524ac8a1082b3629c4
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
			TargetReport target = vis->getNearestPeg();
			switch(target.region) {
				case NorthWest:
					display->PrintfLine(8, "Target region:      NW");
					break;
				case North:
					display->PrintfLine(8, "Target region:       N");
					break;
				case NorthEast:
					display->PrintfLine(8, "Target region:      NE");
					break;
				case West:
					display->PrintfLine(8, "Target region:       W");
					break;
				case Center:
					display->PrintfLine(8, "Target region:       C");
					break;
				case East:
					display->PrintfLine(8, "Target region:       E");
					break;
				case SouthWest:
					display->PrintfLine(8, "Target region:      SW");
					break;
				case South:
					display->PrintfLine(8, "Target region:       S");
					break;
				case SouthEast:
					display->PrintfLine(8, "Target region:       E");
					break;
				default:
					display->PrintfLine(8, "Target region:     ERR");
			}
			display->PrintfLine(9, "Target area:        %f", (float)target.area);
			float t = -1.0 * joystick->GetThrottle();
			display->SetScrollLocation(t);
			display->Output();
<<<<<<< HEAD
=======
			driver->Drive(x, y, joystick->GetRotation());
>>>>>>> c0cc8be37dc7ea7c4bbbdc524ac8a1082b3629c4
		}
		
		/** Unused functions */
		void DisabledPeriodic(void) {}
		void DisabledContinuous(void) {}
		void AutonomousContinuous(void) {}
		void TeleopContinuous(void) {}
<<<<<<< HEAD
	private:
		DisplayWrapper* display;
		JoystickWrapper* joystick;
		Vision* vis;
=======
		
	private:
		DisplayWrapper* display;
		DriverWrapper* driver;
		JoystickWrapper* joystick;
>>>>>>> c0cc8be37dc7ea7c4bbbdc524ac8a1082b3629c4
};

START_ROBOT_CLASS(BetaRobot);
