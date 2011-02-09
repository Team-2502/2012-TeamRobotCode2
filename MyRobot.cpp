#include <math.h>
#include <Dashboard.h>
#include "WPILib.h"

#include "DisplayWrapper.h"
#include "DriverWrapper.h"
#include "JoystickWrapper.h"
#include "VisionRoutines.h"
#include "Vision/PCVideoServer.h"

class BetaRobot : public IterativeRobot
{
	public:
		BetaRobot(void)
		{
			joystick[0] = new JoystickWrapper(1, Extreme3DPro);
			joystick[1] = new JoystickWrapper(2, Attack3);
			joystick[2] = new JoystickWrapper(3, DualAction);
			joy = 0;
			for(int i = 0; i < 3; i++)
			{
				joystick[i]->SetSnapPoints(8);
			}
			//vis = Vision::GetInstance();
			display = new DisplayWrapper();
			driver = new DriverWrapper(Mecanum);
			//pcvs = new PCVideoServer;
		}
	
		void RobotInit(void) {}
		void DisabledInit(void) {/*pcvs->Stop();*/}
		void AutonomousInit(void) {}
		void TeleopInit(void) {/*pcvs->Start();*/}
		void AutonomousPeriodic(void) {}
		
		void TeleopPeriodic(void)
		{
			float x, y;
			joystick[joy]->GetAxis(&x, &y);
			
			display->PrintfLine(0, "Joystick Angle:     %f", joystick[joy]->GetAngle());
			display->PrintfLine(1, "Joystick Throttle:  %f", joystick[joy]->GetThrottle());
			display->PrintfLine(2, "Joystick X: %f", x);
			display->PrintfLine(3, "Joystick Y: %f", y);
			display->PrintfLine(4, "Joystick Magnitude: %f", joystick[joy]->GetMagnitude());
			display->PrintfLine(5, "Joystick Rotation:  %f", joystick[joy]->GetRotation());
			if(joystick[0]->GetJoystick()->GetRawButton(7))
				joy = 0;
			else if(joystick[0]->GetJoystick()->GetRawButton(9))
				joy = 1;
			else if(joystick[0]->GetJoystick()->GetRawButton(11))
				joy = 2;
			/*
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
			*/
			float t = -1.0 * joystick[0]->GetThrottle();
			display->SetScrollLocation(t);
			driver->Drive(x, y, joystick[0]->GetRotation());
			display->Output();
		}
		
		/** Unused functions */
		void DisabledPeriodic(void) {}
		void DisabledContinuous(void) {}
		void AutonomousContinuous(void) {}
		void TeleopContinuous(void) {}
		
	private:
		int joy;
		DisplayWrapper* display;
		JoystickWrapper* joystick[3];
		//Vision* vis;
		DriverWrapper* driver;
		//PCVideoServer* pcvs;
};

START_ROBOT_CLASS(BetaRobot);
