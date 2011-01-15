#include <math.h>
#include <Dashboard.h>
#include "WPILib.h"
#include "Pneumatics.h"
#define AxisButton 11
#define ZeroButton 12

class BetaRobot : public IterativeRobot
{
	public:
		BetaRobot(void)
		{
			m_frontLeftMotor = new Jaguar(7);
			m_frontRightMotor = new Jaguar(3);
			m_rearLeftMotor = new Jaguar(1);
			m_rearRightMotor = new Jaguar(2);
			driveStick = new Joystick(1);
			PneumaticsButtons buttons;
			buttons.autoButton = 12;
			buttons.kickButton = 1; //Trigger
			buttons.manualButton = 11;
			buttons.liftButton = 7;
			pSystem = new PneumaticSystem(buttons, driveStick);
			#ifdef DEBUG
			driverStationLCD = DriverStationLCD::GetInstance();
			showingSpeeds = true;
			lastStateTrigger = driveStick->GetRawButton(AxisButton);
			#endif
		}
		
		void Normalize(double *wheelSpeeds)
		{
			double maxMagnitude = fabs(wheelSpeeds[0]);
			int i;
			for (i=1; i<4; i++)
			{
				double temp = fabs(wheelSpeeds[i]);
				if (maxMagnitude < temp) maxMagnitude = temp;
			}
			if (maxMagnitude > 1.0)
			{
				for (i=0; i < 4; i++)
				{
					wheelSpeeds[i] = wheelSpeeds[i] / maxMagnitude;
				}
			}
		}
		
		void Drive(float x, float y, float rotation)
		{
			double xIn = x;
			double yIn = -y; // Negate y for the joystick.
			
			double wheelSpeeds[4];
			wheelSpeeds[RobotDrive::kFrontLeftMotor] = xIn + yIn + rotation;
			wheelSpeeds[RobotDrive::kFrontRightMotor] = -xIn + yIn - rotation;
			wheelSpeeds[RobotDrive::kRearLeftMotor] = -xIn + yIn + rotation;
			wheelSpeeds[RobotDrive::kRearRightMotor] = xIn + yIn - rotation;
			
			Normalize(wheelSpeeds);
			
			m_frontLeftMotor->Set(wheelSpeeds[RobotDrive::kFrontLeftMotor]);
			m_frontRightMotor->Set(-1*wheelSpeeds[RobotDrive::kFrontRightMotor]);
			m_rearLeftMotor->Set(wheelSpeeds[RobotDrive::kRearLeftMotor]);
			m_rearRightMotor->Set(-1*wheelSpeeds[RobotDrive::kRearRightMotor]);
			#ifdef DEBUG
			sendDataToDS();
			#endif
		}
		
		
		void RobotInit(void) {pSystem->start();}
		void DisabledInit(void) {pSystem->stop();}
		void AutonomousInit(void) {pSystem->setCompressor(true);}
		void TeleopInit(void) {pSystem->start();}
		
		void AutonomousPeriodic(void) { GetWatchdog().Feed(); }
		void TeleopPeriodic(void)
		{
			GetWatchdog().Feed();
			Drive(driveStick->GetRawAxis(Joystick::kYAxis),
				  driveStick->GetRawAxis(Joystick::kZAxis),
				  driveStick->GetRawAxis(Joystick::kTwistAxis));
			#ifdef DEBUG
			if(driveStick->GetRawButton(AxisButton) && !lastStateTrigger) {
				showingSpeeds = !showingSpeeds;
			}
			lastStateTrigger = driveStick->GetRawButton(AxisButton);
			#endif
		}
		
		/** Unused functions */
		void DisabledPeriodic(void) {}
		void DisabledContinuous(void) {}
		void AutonomousContinuous(void) {}
		void TeleopContinuous(void) {}
		
		#ifdef DEBUG
		void sendDataToDS() {
			if(showingSpeeds) {
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line1,"Speed FL: %f",m_frontLeftMotor->Get());
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line2,"Speed FR: %f",m_frontRightMotor->Get());
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line3,"Speed RL: %f",m_rearLeftMotor->Get());
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line4,"Speed RR: %f",m_rearRightMotor->Get());
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line5,"");
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line6,"");
			} else {
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line1,"Joystick X: %f",0.0);
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line2,"Joystick Y: %f",driveStick->GetRawAxis(Joystick::kYAxis));
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line3,"Joystick Z: %f",driveStick->GetRawAxis(Joystick::kZAxis));
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line4,"Joystick T: %f",driveStick->GetRawAxis(Joystick::kTwistAxis));
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line5,"");
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line6,"");
			}
			driverStationLCD->UpdateLCD();
		}
		#endif
		
	private:
		#ifdef DEBUG
		DriverStationLCD* driverStationLCD;
		bool showingSpeeds;
		bool lastStateTrigger;
		#endif
		Joystick *driveStick;
		PneumaticSystem *pSystem;
		SpeedController *m_frontLeftMotor;
		SpeedController *m_frontRightMotor;
		SpeedController *m_rearLeftMotor;
		SpeedController *m_rearRightMotor;
};

START_ROBOT_CLASS(BetaRobot);

