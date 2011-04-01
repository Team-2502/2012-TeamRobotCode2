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
	~DriverWrapper();
	
	/**
	 * Drive. X, Y, and Rotation come from the joystick and the gyroAngle
	 * should be passed in from the Gyro.
	 */
	void Drive(float x, float y, float rotation, float gyroAngle = 0.0);
	void setFieldOrientedDrive(bool b) { useFOD = b; }
	void toggleInversion();
	
private:
	Jaguar* frontLeft;
	Jaguar* frontRight;
	Jaguar* rearLeft;
	Jaguar* rearRight;
	DriveType type;
	
	bool invertControls;
	
	void MecanumDrive(float x, float y, float rotation, float gyroAngle);
	void TankDrive(float x, float y, float rotation);
	bool useFOD;
};

#endif // DRIVERWRAPPER_H
