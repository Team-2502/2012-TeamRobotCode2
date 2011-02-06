#ifndef CONFIG_H
#define CONFIG_H

#define JOYSTICK_PORT 1
#define FRONT_LEFT_CHANNEL 3
#define REAR_LEFT_CHANNEL 1
#define FRONT_RIGHT_CHANNEL 4
#define REAR_RIGHT_CHANNEL 2
#define TWO_CHANNEL_ACCEL_SLOT 1 //tentative
#define TWO_CHANNEL_ACCEL_X 11   //tentative
#define TWO_CHANNEL_ACCEL_Y 12   //tentative

//#define USE_GYRO
#ifdef USE_GYRO
	#define GYRO_SLOT 1
	#define GYRO_CHANNEL 1
	#define GYRO_HEAT_CHANNEL 2
	#define GYRO_MULT -1
#endif


#endif
