#include "C:/Progra~1/WindRiver/vxworks-6.3/target/h/WPIlib/WPILib.h"

class DisplayRobot : public IterativeRobot
{
	public:
		DisplayRobot(void)
		{
			joy=Joystick_Wrapper(1);
			driverStationLCD = DriverStationLCD::GetInstance();
		};
		void AutonomousPeriodic(void) {};
		void TeleopPeriodic(void)
		{
			driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line1,"Joystick X: %f",joy->getX());
			driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line2,"Joystick Y: %f",joy->getY());
			driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line3,"Joystick Z: %f",joy->getTwist());
			driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line4,"Joystick T: %f",joy->getThrottle());
			driverStationLCD->PrintfLine(DriverStationLCD::kUser_Line5,"Joystick H: %f",joy->getPOV());
			driverStationLCD->UpdateLCD();
		}
	private:
		Joystick_Wrapper* joy;
		DriverStationLCD* driverStationLCD;
};

START_ROBOT_CLASS(DisplayRobot);

