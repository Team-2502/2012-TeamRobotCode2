#include <cmath>

#include "DriverWrapper.h"

void Normalize(double *wheelSpeeds)
{
	double maxMagnitude = fabs(wheelSpeeds[0]);
	INT32 i;
	for (i=1; i<4; i++)
	{
		double temp = fabs(wheelSpeeds[i]);
		if (maxMagnitude < temp) maxMagnitude = temp;
	}
	if (maxMagnitude > 1.0)
	{
		for (i=0; i<4; i++)
		{
			wheelSpeeds[i] = wheelSpeeds[i] / maxMagnitude;
		}
	}
}

void RotateVector(double &x, double &y, double angle)
{
	double cosA = cos(angle * (3.14159 / 180.0));
	double sinA = sin(angle * (3.14159 / 180.0));
	double xOut = x * cosA - y * sinA;
	double yOut = x * sinA + y * cosA;
	x = xOut;
	y = yOut;
}

DriverWrapper::DriverWrapper(DriveType type, UINT32 frontLeftMotorChannel, 
		UINT32 rearLeftMotorChannel, UINT32 frontRightMotorChannel, UINT32 rearRightMotorChannel)
{
	this->frontLeft = new Victor(FRONT_LEFT_CHANNEL);
	this->rearLeft = new Victor(REAR_LEFT_CHANNEL);
	this->frontRight = new Victor(FRONT_RIGHT_CHANNEL);
	this->rearRight = new Victor(REAR_RIGHT_CHANNEL);
	this->frontLeft->SetSafetyEnabled(false);
	this->rearLeft->SetSafetyEnabled(false);
	this->frontRight->SetSafetyEnabled(false);
	this->rearRight->SetSafetyEnabled(false);
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
		MecanumDrive(x, y, rotation, gyroAngle);
		break;
		
	case Tank:
		/// :TODO: Implement this if we need it
		break;
	}
}

void DriverWrapper::MecanumDrive(float x, float y, float rotation, float gyroAngle)
{
	double xIn = x;
	double yIn = y;
	
	// Compenstate for gyro angle.
	//RotateVector(xIn, yIn, gyroAngle);

	double wheelSpeeds[4];

	wheelSpeeds[RobotDrive::kFrontLeftMotor] = xIn + yIn + rotation;
	wheelSpeeds[RobotDrive::kFrontRightMotor] = -xIn + yIn - rotation;
	wheelSpeeds[RobotDrive::kRearLeftMotor] = -xIn + yIn + rotation;
	wheelSpeeds[RobotDrive::kRearRightMotor] = xIn + yIn - rotation;

	Normalize(wheelSpeeds);

	frontLeft->Set(wheelSpeeds[RobotDrive::kFrontLeftMotor]);
	frontRight->Set(-1*wheelSpeeds[RobotDrive::kFrontRightMotor]);
	rearLeft->Set(wheelSpeeds[RobotDrive::kRearLeftMotor]);
	rearRight->Set(-1*wheelSpeeds[RobotDrive::kRearRightMotor]);
}
