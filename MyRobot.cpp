#include <math.h>

#include <Dashboard.h>
#include "WPILib.h"

#include "JoystickWrapper.h"
//#include "Pneumatics.h"

#define AxisButton 11
#define ZeroButton 12
//#define DEBUG
class BetaRobot : public IterativeRobot
{
	public:
		BetaRobot(void)
		{
			//m_frontLeftMotor = new Victor(7);
			//m_frontRightMotor = new Victor(3);
			//m_rearLeftMotor = new Victor(2);
			//m_rearRightMotor = new Victor(1);
			//driveStick = new Joystick(1);
			joystick = new JoystickWrapper(1, Extreme3DPro);
			joystick->SetSnapPoints(4);
			drive = new RobotDrive(7, 2, 3, 1);
			drive->SetSafetyEnabled(false);
			driverStationLCD = DriverStationLCD::GetInstance();
			//m_frontLeftMotor->SetSafetyEnabled(false);
			//m_frontRightMotor->SetSafetyEnabled(false);
			//m_rearLeftMotor->SetSafetyEnabled(false);
			//m_rearRightMotor->SetSafetyEnabled(false);
			//PneumaticsButtons buttons;
			//buttons.autoButton = 12;
			//buttons.kickButton = 1; //Trigger
			//buttons.manualButton = 11;
			//buttons.liftButton = 7;
			//pSystem = new PneumaticSystem(buttons, driveStick);
			#ifdef DEBUG
			driverStationLCD = DriverStationLCD::GetInstance();
			showingSpeeds = false;
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
			
			//m_frontLeftMotor->Set(wheelSpeeds[RobotDrive::kFrontLeftMotor]);
			//m_frontRightMotor->Set(-1*wheelSpeeds[RobotDrive::kFrontRightMotor]);
			//m_rearLeftMotor->Set(wheelSpeeds[RobotDrive::kRearLeftMotor]);
			//m_rearRightMotor->Set(-1*wheelSpeeds[RobotDrive::kRearRightMotor]);
			#ifdef DEBUG
			sendDataToDS();
			#endif
		}
		
		
		void RobotInit(void) {/*pSystem->start();*/}
		void DisabledInit(void) {/*pSystem->stop();*/}
		void AutonomousInit(void) {/*pSystem->setCompressor(true);*/}
		void TeleopInit(void) {/*pSystem->start();*/}
		
		void AutonomousPeriodic(void) 
		{
			GetWatchdog().Feed();
			
			//Drive(0.0, 0.05, 0.0);
		}
		void TeleopPeriodic(void)
		{
			GetWatchdog().Feed();
#if 1
			/*
			Drive(driveStick->GetRawAxis(Joystick::kYAxis),
				  driveStick->GetRawAxis(Joystick::kZAxis),
				  driveStick->GetRawAxis(Joystick::kTwistAxis));
			*/
			
			float x, y;
			joystick->GetRawAxis(&x, &y);
			//Drive(x, y, joystick->GetJoystick()->GetRawAxis(Joystick::kTwistAxis));
			drive->MecanumDrive_Cartesian(x, y, joystick->GetJoystick()->GetRawAxis(Joystick::kTwistAxis));
			
			/*
			driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line1,"Joystick X Axis: %f",joystick->GetJoystick()->GetRawAxis(Joystick::kDefaultXAxis));
			driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line2,"Joystick Y Axis: %f",joystick->GetJoystick()->GetRawAxis(Joystick::kDefaultYAxis));
			driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line3,"Joystick Z Axis: %f",joystick->GetJoystick()->GetRawAxis(Joystick::kDefaultZAxis));
			driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line4,"Joystick W Axis: %f",joystick->GetJoystick()->GetRawAxis(Joystick::kDefaultTwistAxis));
			driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line5,"Joystick T Axis: %f",joystick->GetJoystick()->GetRawAxis(Joystick::kDefaultThrottleAxis));
			*/
			
			driverStationLCD->UpdateLCD();
#else
			if(driveStick->GetRawButton(5))
				m_frontLeftMotor->Set(0.1);
			else
				m_frontLeftMotor->Set(0.0);
			if(driveStick->GetRawButton(6))
				m_frontRightMotor->Set(0.1);
			else
				m_frontRightMotor->Set(0);
			if(driveStick->GetRawButton(3))
				m_rearLeftMotor->Set(0.1);
			else
				m_rearLeftMotor->Set(0);
			if(driveStick->GetRawButton(4))
				m_rearRightMotor->Set(0.1);
			else
				m_rearRightMotor->Set(0);
#endif
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
		DriverStationLCD* driverStationLCD;
		//Joystick *driveStick;
		//PneumaticSystem *pSystem;
		RobotDrive* drive;
		JoystickWrapper* joystick;
		Victor *m_frontLeftMotor;
		Victor *m_frontRightMotor;
		Victor *m_rearLeftMotor;
		Victor *m_rearRightMotor;
};

START_ROBOT_CLASS(BetaRobot);

