#ifndef CONFIG_H
#define CONFIG_H

#define JOYSTICK_PORT 1
#define FRONT_LEFT_CHANNEL 3
#define REAR_LEFT_CHANNEL 1
#define FRONT_RIGHT_CHANNEL 4
#define REAR_RIGHT_CHANNEL 2
#define WINCH_CHANNEL 5 //tentative
#define LEFT_CLAW_CHANNEL 6 //tentative
#define RIGHT_CLAW_CHANNEL 314159 //tentative
#define TWO_CHANNEL_ACCEL_SLOT 1 //tentative
#define TWO_CHANNEL_ACCEL_X 11   //tentative
#define TWO_CHANNEL_ACCEL_Y 12   //tentative
#define RIGHT_CLAW_ENCODER_A_CHANNEL 314159 //dummy
#define RIGHT_CLAW_ENCODER_B_CHANNEL 314159 //dummy
#define LEFT_CLAW_ENCODER_A_CHANNEL 314159 //dummy
#define LEFT_CLAW_ENCODER_B_CHANNEL 314159 //dummy
#define ARM_CHAIN_ENCODER_A_CHANNEL 314159 //dummy
#define ARM_CHAIN_ENCODER_B_CHANNEL 314159 //dummy
#define SERVO_CHANNEL 7
#define DIGITAL_SIDECAR_PORT 1

#define USE_GYRO
#ifdef USE_GYRO
	#define GYRO_SLOT 0
	#define GYRO_CHANNEL 0
	#define GYRO_HEAT_CHANNEL 1
	#define GYRO_MULT -1
#endif

#define INIT_ARM_HEIGHT 314159 //dummy
#define INIT_CLAW_WIDTH 314159 //dummy
#define PID_P 20
#define PID_I 0 //7
#define PID_D 0 //20

#define XRESOLUTION 640 //IDK what this should be
#define YRESOLUTION 480 //IDK what this should be

#define ROT_EXPONENTIAL 50 // Tweak this
#define MAG_EXPONENTIAL 10

const float PIE = 3.141592653897;

#endif
