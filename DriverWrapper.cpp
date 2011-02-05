#include "DriverWrapper.h"

DriverWrapper::DriverWrapper(DriveType type, UINT32 frontLeftMotorChannel, 
		UINT32 rearLeftMotorChannel, UINT32 frontRightMotorChannel, UINT32 rearRightMotorChannel)
{
	this->type = type;
	this->driver = new RobotDrive(frontLeftMotorChannel, rearLeftMotorChannel, frontRightMotorChannel, rearRightMotorChannel);
}

void DriverWrapper::Drive(float x, float y, float rotation, float gyroAngle)
{
	switch(static_cast<int>(this->type))
	{
	case Mecanum:
		this->driver->MecanumDrive_Cartesian(x, y, rotation, gyroAngle);
		break;
		
	case Tank:
		/// :TODO: Implement this if we need it
		break;
	}
}
