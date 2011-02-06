#ifndef DRIVERWRAPPER_H
#define DRIVERWRAPPER_H

#include <WPILib.h>

enum DriveType
{
	Mecanum,
	Tank,
};

/**
 * Wraps around the drive system for the robot.
 */
class DriverWrapper
{
public:
	DriverWrapper(DriveType type, UINT32 frontLeftMotorChannel, 
			UINT32 rearLeftMotorChannel, UINT32 frontRightMotorChannel, UINT32 rearRightMotorChannel);
	
	/**
	 * Drive. X, Y, and Rotation come from the joystick and the gyroAngle
	 * should be passed in from the Gyro.
	 */
	void Drive(float x, float y, float rotation, float gyroAngle = 0.0);
	
private:
	Victor* frontLeft;
	Victor* frontRight;
	Victor* rearLeft;
	Victor* rearRight;
	DriveType type;
	
	void MecanumDrive(float x, float y, float rotation, float gyroAngle);
};

#endif // DRIVERWRAPPER_H
