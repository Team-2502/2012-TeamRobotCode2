#include "DriverWrapper.h"

DriverWrapper::DriverWrapper(DriveType type)
{
	this->type = type;
	this->driver = new RobotDrive(FRONT_LEFT_CHANNEL, REAR_LEFT_CHANNEL, FRONT_RIGHT_CHANNEL, REAR_RIGHT_CHANNEL);
	useFOD = true;
	#ifdef USE_GYRO
	gyro = new Gyro(GYRO_SLOT,GYRO_CHANNEL);
	#endif
}

void DriverWrapper::Drive(float x, float y, float rotation)
{
	static float gyroAngle = 0.0;
	#ifdef USE_GYRO
	if(useFOD)
		gyroAngle = gyro->GetAngle() * GYRO_MULT;
	#endif
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
