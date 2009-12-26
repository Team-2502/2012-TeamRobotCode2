#include "WPILib.h"

class RobotDemo : public SimpleRobot
{
private:
	RobotDrive team2502Bot; // robot drive system
	Joystick driveStick; // only joystick
	Joystick driveStick2;
	
public:
	RobotDemo(void):
		team2502Bot(1, 2),	// these must be initialized in the same order
		driveStick(1),		// as they are declared above.
		driveStick2(2)
	{
		GetWatchdog().SetExpiration(0.1);
	}

	/**
	 * Drive left & right motors for 2 seconds then stop
	 */
	void Autonomous(void)
	{
//		GetWatchdog().SetEnabled(false);
//		myRobot.Drive(0.5, 0.0); 	// drive forwards half speed
//		Wait(2.0); 				//    for 2 seconds
//		myRobot.Drive(0.0, 0.0); 	// stop robot
	}

	/**
	 * Runs the motors with arcade steering. 
	 */
	void OperatorControl(void)
	{
		GetWatchdog().SetEnabled(true);
		while (IsOperatorControl())
		{
			GetWatchdog().Feed();
			float speed = driveStick.GetY();
			float speed2 = driveStick2.GetY();
			team2502Bot.TankDrive(speed,speed2);
			//team2502Bot.ArcadeDrive(driveStick); // drive with arcade style (use right stick)
			Wait(0.005);				// wait for a motor update time
		}
	}
	
};

START_ROBOT_CLASS(RobotDemo);

