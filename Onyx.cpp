#include "WPILib.h"
class Onyx : public IterativeRobot //Onyx is our Code Name for 2009 year.
{
	// Declare variable for the robot drive system
	// The "r" prefix stands for "Robot" which is going to be our prefix for variables that are independent of the operator/driver.
	RobotDrive *r_robotDrive; // robot will use PWM 1-4 for drive motors


	// Declare variables for the two joysticks being used
	// The "o" prefix stands for "operator" meaning that these will be used for the brushes
	Joystick *o_rightStick; // joystick 1 (lower brushes)
	Joystick *o_leftStick; // joystick 2 (upper brushes)
	Joystick *d_driveStick; // joystick 3 (driving w/ Twist)
	
	// Local Variables to keep track of Joystick postitions
	// TODO: See if the set of variables can be optimized
	float o_rightStick_x;
	float o_rightStick_y;
	float o_leftStick_x;
	float o_leftStick_y;
	float d_driveStick_x;
	float d_driveStick_y;
	float d_driveStick_z;

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
		r_robotDrive = new RobotDrive(1, 3, 2, 4);

		// Define joysticks being used at USB port #1 and USB port #2 on the Drivers Station
		o_rightStick = new Joystick(1);
		o_leftStick = new Joystick(2);
		d_driveStick = new Joystick(3);

		// Iterate over all the buttons on each joystick, setting state to false for each
		UINT8 t_buttonNum = 1; // start counting buttons at button 1
		for (t_buttonNum = 1; t_buttonNum <= NUM_JOYSTICK_BUTTONS; t_buttonNum++) {
			o_rightStickButtonState[t_buttonNum] = false;
			o_leftStickButtonState[t_buttonNum] = false;
			d_driveStickButtonState[t_buttonNum] = false;
		}

		// Set drive mode to uninitialized
		r_driveMode = UNINIT_DRIVE;

		// Initialize counters to record the number of loops completed in autonomous and teleop modes
		r_autoPeriodicLoops = 0;
		r_disabledPeriodicLoops = 0;
		r_telePeriodicLoops = 0;

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
	}

	/********************************** Periodic Routines *************************************/

	void DisabledPeriodic(void) {
		static INT32 printSec = (INT32)GetClock() + 1;
		static const INT32 startSec = (INT32)GetClock();

		// feed the user watchdog at every period when disabled
		GetWatchdog().Feed();

		// increment the number of disabled periodic loops completed
		r_disabledPeriodicLoops++;

		// while disabled, printout the duration of current disabled mode in seconds
		if (GetClock() > printSec) {
			// Move the cursor back to the previous line and clear it.
			printf("\x1b[1A\x1b[2K"); //Move up one line, delete the line
			printf("Disabled seconds: %d\r\n", printSec - startSec);	
			printSec++;
		}
	}

	void AutonomousPeriodic(void) {
		// feed the user watchdog at every period when in autonomous
		GetWatchdog().Feed();

		r_autoPeriodicLoops++;

		/* BELOW CODE IS COMMENTED OUT FOR SAFETY.
		 * BUT DO UNDERSTAND IT. WHAT IT DOES AND HOW.
		 if (r_autoPeriodicLoops == 1) {
		 // When on the first periodic loop in autonomous mode,
		 // start driving forwards at half speed
		 r_robotDrive->Drive(0.5, 0.0);			// drive forwards at half speed
		 }
		 if (r_autoPeriodicLoops == (2 * GetLoopsPerSec())) {
		 // After 2 seconds, stop the robot 
		 r_robotDrive->Drive(0.0, 0.0);			// stop robot
		 }
		 */
	}

	void TeleopPeriodic(void) {
		// feed the user watchdog at every period when in autonomous
		GetWatchdog().Feed();
		
		d_driveStick_x = d_driveStick->GetX();
		d_driveStick_y = d_driveStick->GetY();

		// increment the number of teleop periodic loops completed
		r_telePeriodicLoops++;

		/* Do some actual Joystick driving here
		 * As we have more driving modes, we just add more "else if"s.
		 * */
		if (r_driveMode == MAGIC_DRIVE) { // Logitech Attack3 has z-polarity reversed; up is negative
			// use Magic Drive mode
			r_robotDrive->SetLeftRightMotorSpeeds(
					d_driveStick_y-d_driveStick_x,
					-d_driveStick_y+d_driveStick_x); //Negated becase that's how the joystick behaves
		}

	} // TeleopPeriodic(void)


	/********************************** Continuous Routines *************************************/

	/* 
	 * These routines are not used in this demonstration robot
	 *
	 * 
	 void DisabledContinuous(void) {
	 }

	 void AutonomousContinuous(void)	{
	 }

	 void TeleopContinuous(void) {
	 }
	 */

	/********************************** Miscellaneous Routines *************************************/

};//Class End

START_ROBOT_CLASS(Onyx);
