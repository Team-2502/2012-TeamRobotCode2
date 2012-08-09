#ifndef CONSTANTS_H
#define CONSTANTS_H

#define __UNUSED(x) (void)(x);

//Physical constants (in U.S. units (feet), not metric)
const double BALL_RADIUS = 8.0 / 12.0;
const double BASKET_RADIUS = 18.0 / 12.0;
const double BASKET_BOTTOM_ELEVATION = 28.0 / 12.0;
const double BASKET_MIDDLE_ELEVATION = 61.0 / 12.0;
const double BASKET_TOP_ELEVATION = 98.0 / 12.0;
const double SHOOTER_ELEVATION = 4.0; ///\todo find this
const double SHOOTER_ANGLE = 45.0; ///\todo find this
const double BASKET_BACKBOARD_HEIGHT = 22.0 / 12.0;
const double TURRET_LAZY_SUSAN_DIAMETER = (12 + (13.0 / 16.0)) / 12.0;
const double TURRET_WHEEL_DIAMETER = (2 + (7.0 / 8.0)) / 12.0;

//Wiring constants
const unsigned DIGITAL_SIDECAR_SLOT 		= 1;    //Jaguar
const unsigned DRIVE_LEFT_CHANNEL 			= 1;    //Jaguar
const unsigned DRIVE_RIGHT_CHANNEL 			= 2;    //Jaguar
const unsigned SHOOTER_BOTTOM_JAG_CHANNEL 	= 3; 	//Jaguar
const unsigned SHOOTER_TOP_JAG_CHANNEL 		= 4;    //Jaguar
const unsigned COLLECTOR_LIFTER_CHANNEL 	= 5;   	//Victor
const unsigned COLLECTOR_GRABBER_CHANNEL 	= 6;  	//Victor
const unsigned TURRET_CHANNEL 				= 7;    //Victor


//const unsigned RAMP_LEFT_SPIKE_RELAY 		= 1;    //Spike Relay (unused now)
const unsigned RAMP_SPIKE_RELAY	 			= 1;   	//Spike Relay
const unsigned RAMP_VICTOR_CHANNEL			= 8;

/*   old
const unsigned DRIVE_LEFT_ENCODER_A     = 4;
const unsigned DRIVE_LEFT_ENCODER_B     = 5;
const unsigned DRIVE_RIGHT_ENCODER_A    = 6;
const unsigned DRIVE_RIGHT_ENCODER_B    = 7;
const unsigned SHOOTER_BOTTOM_ENCODER_A = 8;
const unsigned SHOOTER_BOTTOM_ENCODER_B = 9;
const unsigned SHOOTER_TOP_ENCODER_A    = 10;
const unsigned SHOOTER_TOP_ENCODER_B    = 11;
const unsigned TURRET_ENCODER_A         = 12;
const unsigned TURRET_TOP_ENCODER_B     = 13;
*/

const unsigned DRIVE_LEFT_ENCODER_A     = 1;
const unsigned DRIVE_LEFT_ENCODER_B     = 2;
const unsigned DRIVE_RIGHT_ENCODER_A    = 3;
const unsigned DRIVE_RIGHT_ENCODER_B    = 4;
//const unsigned SHOOTER_BOTTOM_ENCODER_A = 5;
//const unsigned SHOOTER_BOTTOM_ENCODER_B = 6;
//const unsigned SHOOTER_TOP_ENCODER_A    = 7;
//const unsigned SHOOTER_TOP_ENCODER_B    = 8;
const unsigned SHOOTER_BOTTOM_ENCODER_A = 5;
//const unsigned SHOOTER_BOTTOM_ENCODER_B = 6;
const unsigned SHOOTER_TOP_ENCODER_A    = 6;
//const unsigned SHOOTER_TOP_ENCODER_B    = 8;
const unsigned TURRET_ENCODER_A         = 9;
const unsigned TURRET_ENCODER_B     	= 10;


// Analog constants
const unsigned IR_FRONT_CHANNEL         = 1;
const unsigned IR_FRONT_MIDDLE_CHANNEL	= 2;
const unsigned IR_MIDDLE_CHANNEL        = 4;
const unsigned IR_TOP_CHANNEL           = 3;

// Shooter constants
const double TURRET_SIGNAL_VOLTAGE		= 3.0;
const double TURRET_SPEED				= 0.25;
const unsigned TURRET_ENCODER_PULSES	= 100; // Found this

// Collector Constants
const unsigned BALL_VISIBLE									= 1;
const unsigned BALL_NOT_VISIBLE								= 0;
const unsigned MAX_BALLS									= 3;
const double   COLLECTOR_RUNFAST							= 1.0;
const double   COLLECTOR_RUNSLOW							= 0.5;
const double   COLLECTOR_RUNFAST_REVERSE					= -1.0;
const double   COLLECTOR_RUNSLOW_REVERSE					= -0.5;
const double   COLLECTOR_STOP								= 0.0;
const double   COLLECTOR_FRONT_SIGNAL_VOLTAGE 				= 0.5;
const double   COLLECTOR_FRONT_MIDDLE_SIGNAL_VOLTAGE 		= 0.8;
const double   COLLECTOR_MIDDLE_SIGNAL_VOLTAGE 				= 1.5;
const double   COLLECTOR_TOP_SIGNAL_VOLTAGE 				= 0.85;
const unsigned COLLECTOR_FRONT_SIGNAL_TOGGLE_COUNT			= 10; 
const unsigned COLLECTOR_FRONT_MIDDLE_SIGNAL_TOGGLE_COUNT	= 40; 
const unsigned COLLECTOR_MIDDLE_SIGNAL_TOGGLE_COUNT			= 10; 
const unsigned COLLECTOR_TOP_SIGNAL_TOGGLE_COUNT			= 20;
const unsigned COLLECTOR_WAIT_TIME							= 3000;

// Button Mappings
const unsigned TURRET_BUTTON					= 2;
const unsigned BALANCE_ROBOT_BUTTON				= 4;
const unsigned RAMP_DOWN_BUTTON					= 5;
const unsigned RAMP_UP_BUTTON					= 3;
const unsigned EJECT_BALLS_BUTTON				= 6;
const unsigned COLLECTOR_ADD_BALL_BUTTON		= 8;
const unsigned COLLECTOR_SUB_BALL_BUTTON		= 7;

// Vision Target Indexers
const unsigned TOP_TARGET						= 0;
const unsigned LEFT_TARGET						= 1;
const unsigned RIGHT_TARGET						= 2;
const unsigned BOTTOM_TARGET					= 3;

//Singletons
#define ROBOT (Singleton<Robot>::GetInstance())
#define COLLECTOR (Singleton<Collector>::GetInstance())
#define SHOOTER (Singleton<Shooter>::GetInstance())
#define DRIVETRAIN (Singleton<DriveTrain>::GetInstance())
#define VISION (Singleton<Vision>::GetInstance())
#define SQUAREFINDER (Singleton<SquareFinder>::GetInstance())
#define LOGGER (Singleton<Logger>::GetInstance())

#endif // CONSTANTS_H 
