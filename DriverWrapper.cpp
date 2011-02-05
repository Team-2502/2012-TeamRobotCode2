#include "DriverWrapper.h"

DriverWrapper::DriverWrapper(DriveType type)
{
	this->type = type;
	this->driver = new RobotDrive(FRONT_LEFT_CHANNEL, REAR_LEFT_CHANNEL, FRONT_RIGHT_CHANNEL, REAR_RIGHT_CHANNEL);
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
