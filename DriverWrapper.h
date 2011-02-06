#ifndef DRIVERWRAPPER_H
#define DRIVERWRAPPER_H

#include <WPILib.h>
#include "config.h"

enum DriveType {
	Mecanum,
	Tank,
};

/**
 * Wraps around the drive system for the robot.
 */
class DriverWrapper
{
public:
	DriverWrapper(DriveType type);
	
	/**
	 * Drive. X, Y, and Rotation come from the joystick and the gyroAngle
	 * should be passed in from the Gyro.
	 */
	void Drive(float x, float y, float rotation);
	void setFieldOrientedDrive(bool b) { useFOD = b; }
	
	RobotDrive* GetRobotDrive() { return this->driver; }
	
private:
	RobotDrive* driver;
	DriveType type;
	bool useFOD;
	#ifdef GYRO_SLOT
	Gyro *gyro;
	#endif
};

#endif // DRIVERWRAPPER_H
