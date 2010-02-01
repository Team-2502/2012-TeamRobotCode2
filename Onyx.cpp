/*************************************************************************
 * Proud production of Team 2502
 * Written for 2009 FIRST FRC Season
 * Licensed under the MIT License (Subject to Change)
 *************************************************************************/

#include "WPILib.h"
class Onyx : public IterativeRobot //Onyx is our Code Name for 2009 year.
{
	// Declare variable for the robot drive system
	// The "r" prefix stands for "Robot" which is going to be our prefix for variables that are independent of the operator/driver.
	RobotDrive	*r_robotDrive; // robot will use PWM 1 & 2 for drive motors
	//Relay		*r_robotKicker; // the robot kicker
	
	
	DriverStationLCD *o_dsLCD;
	DriverStation *o_theDS;

	// Declare variables for the two joysticks being used
	// The "o" prefix stands for "operator" meaning that these will be used for the brushes
//	Joystick *o_rightStick; // joystick 1 (lower brushes)
//	Joystick *o_leftStick; // joystick 2 (upper brushes)
	Joystick *d_driveStick; // joystick 3 (driving w/ Twist)
	
	//Pneumatics
	Solenoid *o_ballKicker;
	Compressor *o_theCompressor;
	Relay *o_theRelay;
	
	// Local Variables to keep track of Joystick postitions
	// TODO: See if the set of variables can be optimized
//	float o_rightStick_x;
//	float o_rightStick_y;
//	float o_leftStick_x;
//	float o_leftStick_y;
	float d_driveStick_x;
	float d_driveStick_y;
	float d_driveStick_t;

	// Create an array of joystick buttons so that we can store on/off positions in them
	static const int NUM_JOYSTICK_BUTTONS = 16; //This is depending on the joystick model
	bool o_rightStickButtonState[(NUM_JOYSTICK_BUTTONS+1)];
	bool o_leftStickButtonState[(NUM_JOYSTICK_BUTTONS+1)];
	bool d_driveStickButtonState[(NUM_JOYSTICK_BUTTONS+1)];

	// This is where we declare all the driving styles/modes, including unitialized.
	enum { // drive mode selection
		UNINIT_DRIVE = 0,
		MAGIC_DRIVE = 1
	} r_driveMode;

	// Local variables to count the number of periodic loops performed
	// We probably won't be using this much.
	UINT32 r_autoPeriodicLoops;
	UINT32 r_disabledPeriodicLoops;
	UINT32 r_telePeriodicLoops;

public:
	/**
	 * Constructor for the robot.
	 */
	Onyx(void) {
		printf("Onyx Constructor Started\n");

		// Create a robot using standard right/left robot drive on PWMS 1, 2, 3, and #4
		r_robotDrive = new RobotDrive(1, 2);
		
		// Define joysticks being used at USB port #1 and USB port #2 on the Drivers Station
//		o_rightStick = new Joystick(1);
//		o_leftStick = new Joystick(2);
		d_driveStick = new Joystick(1);

		// Iterate over all the buttons on each joystick, setting state to false for each
		UINT8 t_buttonNum = 1; // start counting buttons at button 1
		for (t_buttonNum = 1; t_buttonNum <= NUM_JOYSTICK_BUTTONS; t_buttonNum++) {
			o_rightStickButtonState[t_buttonNum] = false;
			o_leftStickButtonState[t_buttonNum] = false;
			d_driveStickButtonState[t_buttonNum] = false;
		}

		// Set drive mode to uninitialized
		r_driveMode = UNINIT_DRIVE;

		//Solenoids
		o_ballKicker = new Solenoid(1);
		//Compressor::Compressor (UINT32 pressureSwitchChannel, UINT32 compressorRelayChannel) 	
		o_theCompressor = new Compressor(3,1);
		o_theCompressor->Start();
		o_theRelay = new Relay(1);
		
		// Initialize counters to record the number of loops completed in autonomous and teleop modes
		r_autoPeriodicLoops = 0;
		r_disabledPeriodicLoops = 0;
		r_telePeriodicLoops = 0;

		
		//Driver's Station
		o_theDS = DriverStation::GetInstance();
	    o_dsLCD = DriverStationLCD::GetInstance();
		
		printf("Onyx Constructor Completed\n");
	}

	/********************************** Init Routines *************************************/

	void RobotInit(void) {
		// Actions which would be performed once (and only once) upon initialization of the
		// robot would be put here.

		printf("Onyx: RobotInit() completed.\n");
	}

	void DisabledInit(void) {
		r_disabledPeriodicLoops = 0; // Reset the loop counter for disabled mode

		// Move the cursor down a few, since we'll move it back up in periodic.
		// This funky looking code is part of the ANSI Escape Sequences.
		// It's how command line editors have its permanent place in shell until the program is over.
		// http://ascii-table.com/ansi-escape-sequences.php
		printf("\x1b[2B"); //Move down 2 lines.
	}

	void AutonomousInit(void) {
		r_autoPeriodicLoops = 0; // Reset the loop counter for autonomous mode
	}

	void TeleopInit(void) {
		r_telePeriodicLoops = 0; // Reset the loop counter for teleop mode
		r_driveMode = UNINIT_DRIVE; // Set drive mode to uninitialized
		
		o_theRelay->Set(Relay::kOff);

	}

	/********************************** Periodic Routines *************************************/

	void DisabledPeriodic(void) {
		// feed the user watchdog at every period when disabled
		GetWatchdog().Feed();

		// increment the number of disabled periodic loops completed
		r_disabledPeriodicLoops++;
	}

	void AutonomousPeriodic(void) {
		// feed the user watchdog at every period when in autonomous
		GetWatchdog().Feed();

		r_autoPeriodicLoops++;
	}

	void TeleopPeriodic(void) {
		// feed the user watchdog at every period when in autonomous
		GetWatchdog().Feed();
		r_driveMode = MAGIC_DRIVE; // Set drive mode to uninitialized
		
		d_driveStick_x = d_driveStick->GetX();
		d_driveStick_y = d_driveStick->GetY();

		// increment the number of teleop periodic loops completed
		r_telePeriodicLoops++;
		
		o_dsLCD->Printf(DriverStationLCD::kUser_Line1, 1, "X: %.2f", d_driveStick_x);
		o_dsLCD->Printf(DriverStationLCD::kUser_Line2, 1, "Y: %.2f", d_driveStick_y);


		/* Do some actual Joystick driving here
		 * As we have more driving modes, we just add more "else if"s.
		 * */
		if (r_driveMode == MAGIC_DRIVE) { // Logitech Attack3 has z-polarity reversed; up is negative
			o_dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "Magic? Yes: %.2f", 1);
			// use Magic Drive mode
			
			r_robotDrive->SetLeftRightMotorSpeeds(
					d_driveStick_y+d_driveStick_x,
					d_driveStick_y-d_driveStick_x); //Negated becase that's how the joystick behaves
		} else {
			o_dsLCD->Printf(DriverStationLCD::kUser_Line4, 1, "Magic? No: %.2f", 0);
		}
		
		if (d_driveStick->GetRawButton(12))
		{
			o_dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Button 1? Yes");
			o_theRelay->Set(Relay::kForward);
		}
		else
		{
			o_dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Button 1? No");
			o_theRelay->Set(Relay::kOff);
		}

		
		if (d_driveStick->GetRawButton(11))
		{
			o_dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Button 1? Yes");
			o_theRelay->Set(Relay::kReverse);
		}
		else
		{
			o_dsLCD->Printf(DriverStationLCD::kUser_Line3, 1, "Button 1? No");
			o_theRelay->Set(Relay::kOff);
		}
		
		if (d_driveStick->GetRawButton(1))
		{
			o_dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Shooting");
			o_ballKicker->Set(true);
		}
		else
		{
			o_dsLCD->Printf(DriverStationLCD::kUser_Line5, 1, "Not      ");
			o_ballKicker->Set(false);
		}
		
		o_dsLCD->Printf(DriverStationLCD::kUser_Line6, 1, "%.2f", r_telePeriodicLoops);

		
		o_dsLCD->UpdateLCD();

	} // TeleopPeriodic(void)
};//Class End

START_ROBOT_CLASS(Onyx);
