#include <math.h>
#include "WPILib.h"

enum { AxisButton=11,ZeroButton=12 };

class BetaRobot : public IterativeRobot
{
	public:
		BetaRobot(void)
		{
			gyro = new Gyro(1,8);
			driveStick = new Joystick(1);
			/* m_frontLeftMotor = new Jaguar(4,7);
			m_frontRightMotor = new Jaguar(4,3);
			m_rearLeftMotor = new Jaguar(4,1);
			m_rearRightMotor = new Jaguar(4,2);
			
			m_frontLeftMotor->SetSafetyEnabled(false);
			m_frontRightMotor->SetSafetyEnabled(false);
			m_rearLeftMotor->SetSafetyEnabled(false);
			m_rearRightMotor->SetSafetyEnabled(false); */
			
			driverStationLCD = DriverStationLCD::GetInstance();
			showingSpeeds = true;
			lastStateTrigger = driveStick->GetRawButton(AxisButton);
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
		
		void RotateVector(double &x, double &y, double angle)
		{
			double cosA = cos(angle * (3.14159 / 180.0));
			double sinA = sin(angle * (3.14159 / 180.0));
			double xOut = x * cosA - y * sinA;
			double yOut = x * sinA + y * cosA;
			x = xOut;
			y = yOut;
		}
		
		void Drive(float x, float y, float rotation)
		{
			double xIn = x;
			double yIn = -y; // Negate y for the joystick.
			
			//RotateVector(xIn,yIn,gyro->GetAngle());
			
			double wheelSpeeds[4];
			wheelSpeeds[RobotDrive::kFrontLeftMotor] = xIn + yIn + rotation;
			wheelSpeeds[RobotDrive::kFrontRightMotor] = -xIn + yIn - rotation;
			wheelSpeeds[RobotDrive::kRearLeftMotor] = -xIn + yIn + rotation;
			wheelSpeeds[RobotDrive::kRearRightMotor] = xIn + yIn - rotation;
			
			Normalize(wheelSpeeds);
			
			m_frontLeftMotor->Set(wheelSpeeds[RobotDrive::kFrontLeftMotor]);
			m_frontRightMotor->Set(-1*wheelSpeeds[RobotDrive::kFrontRightMotor]);
			m_rearLeftMotor->Set(-1*wheelSpeeds[RobotDrive::kRearLeftMotor]);
			m_rearRightMotor->Set(wheelSpeeds[RobotDrive::kRearRightMotor]);
			
			
		}
		
		void AutonomousPeriodic(void) { /*Drive(0,0,0);*/ }
		void TeleopPeriodic(void)
		{
			sendDataToDS();
			//Drive(driveStick->GetRawAxis(Joystick::kYAxis),
			//	  driveStick->GetRawAxis(Joystick::kZAxis),
			//	  driveStick->GetRawAxis(Joystick::kTwistAxis));
			if(driveStick->GetRawButton(AxisButton) && lastStateTrigger != driveStick->GetRawButton(AxisButton))
			{
				showingSpeeds = !showingSpeeds;
			}
			lastStateTrigger = driveStick->GetRawButton(AxisButton);
		}
		
		void sendDataToDS() {
			/*if(showingSpeeds) {
				//driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line1,"Speed FL: %f",m_frontLeftMotor->Get());
				//driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line2,"Speed FR: %f",m_frontRightMotor->Get());
				//driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line3,"Speed RL: %f",m_rearLeftMotor->Get());
				//driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line4,"Speed RR: %f",m_rearRightMotor->Get());
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line5,"");
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line6,"");
			}
			else {*/
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line1,"Joystick X: %f",driveStick->GetRawAxis(Joystick::kXAxis));
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line2,"Joystick Y: %f",driveStick->GetRawAxis(Joystick::kYAxis));
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line3,"Joystick Z: %f",driveStick->GetRawAxis(Joystick::kZAxis));
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line4,"Joystick T: %f",driveStick->GetRawAxis(Joystick::kTwistAxis));
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line5,"");
				driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line6,"");
		//	}
			driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line5,"Gyro Angle: %f", gyro->GetAngle());
			driverStationLCD->UpdateLCD();
		}
		
	private:
		Gyro *gyro;
		Joystick *driveStick;
		DriverStationLCD* driverStationLCD;
		bool showingSpeeds;
		bool lastStateTrigger;
		Jaguar *m_frontLeftMotor;
		Jaguar *m_frontRightMotor;
		Jaguar *m_rearLeftMotor;
		Jaguar *m_rearRightMotor;
};

START_ROBOT_CLASS(BetaRobot);

