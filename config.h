#ifndef CONFIG_H
#define CONFIG_H

/*** Features ***/
#define USE_GYRO
#define DEBUG_OUTPUT
#define USE_AUTONOMOUS

/*** Channels ***/

#define JOYSTICK_PORT                     1
#define FRONT_LEFT_CHANNEL                2
#define REAR_LEFT_CHANNEL                 4
#define FRONT_RIGHT_CHANNEL               1
#define REAR_RIGHT_CHANNEL                3
#define WINCH_CHANNEL                     7
#define LEFT_CLAW_CHANNEL                 6 //tentative
#define RIGHT_CLAW_CHANNEL           314159 //tentative
#define TWO_CHANNEL_ACCEL_SLOT            1 //tentative
#define TWO_CHANNEL_ACCEL_X              11 //tentative
#define TWO_CHANNEL_ACCEL_Y              12 //tentative
#define RIGHT_CLAW_ENCODER_A_CHANNEL 314159 //dummy
#define RIGHT_CLAW_ENCODER_B_CHANNEL 314159 //dummy
#define LEFT_CLAW_ENCODER_A_CHANNEL  314159 //dummy
#define LEFT_CLAW_ENCODER_B_CHANNEL  314159 //dummy
#define ARM_CHAIN_ENCODER_A_CHANNEL       1
#define ARM_CHAIN_ENCODER_B_CHANNEL       2
#define SERVO_CHANNEL_START               7

#define DIGITAL_SIDECAR_PORT 4

#define ANALOG_SLOT        1
#define GYRO_SLOT          1
#define GYRO_CHANNEL       1
#define GYRO_HEAT_CHANNEL  2
#define GYRO_MULT          1

#define XRESOLUTION 320
#define YRESOLUTION 240

#define ROT_EXPONENTIAL 50 // Tweak this
#define MAG_EXPONENTIAL 10

#define MANUAL_ARM_SHIFT_X          10
#define MANUAL_ARM_SHIFT_Y          10
#define HIGH_RES_MULTIPLIER          5
#define HORIZONTAL_SNAP_MULTIPLIER 100
#define VERTICAL_SNAP_MULTIPLIER   100

#define LEFT_LINE_CHANNEL   8
#define CENTER_LINE_CHANNEL 9
#define RIGHT_LINE_CHANNEL  10

#define TOP_STOPPER_PORT_L     5
#define TOP_STOPPER_PORT_R     7
#define BOTTOM_STOPPER_PORT_L  4
#define BOTTOM_STOPPER_PORT_R  6

#define MAGNETIC_ENCODER_TOP_CHANNEL    7
#define MAGNETIC_ENCODER_BOTTOM_CHANNEL 8

//correct
#define TOP_GRABBER_CHANNEL    5
#define BOTTOM_GRABBER_CHANNEL 8

/*** CONSTANTS ***/

const float PIE = 3.141592653897;
#define INIT_ARM_HEIGHT 314159 //dummy
#define INIT_CLAW_WIDTH 314159 //dummy
#define PID_P               20
#define PID_I                0
#define PID_D                0
#define MAX_WIDTH       314159 //dummy
#define MAX_LIFT_HEIGHT 314159 //dummy

#endif
