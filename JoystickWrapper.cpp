#include <cmath>

#include "JoystickWrapper.h"

JoystickWrapper::JoystickWrapper(StickType type)
{
	//Initialize stuff
	this->joystick = new Joystick(1);
	
	this->type = type;
	SetSnapPoints(8);
}

float JoystickWrapper::GetAngle() const
{
	float x, y;
	GetRawAxis(&x, &y);
	return (180.0 / std::acos(-1.0)) * std::atan2(x, -1.0 * y);
}

float JoystickWrapper::GetMagnitude() const
{
	float x, y;
	GetRawAxis(&x, &y);
	return std::sqrt(std::pow(x, 2.0) + std::pow(y, 2.0));
}

void JoystickWrapper::GetAxis(float* xaxis, float* yaxis) const
{
	float angle = GetAngle();
	
	//Calculate the angle that we will snap to:
	float snapAngle = std::floor((angle / 360.0) * (float)this->snapPoints) * (360.0 / (float)this->snapPoints);
	snapAngle += 360.0 / (2.0 * (float)this->snapPoints);
	if( snapAngle > 360.0 )
		snapAngle -= 360.0;
	snapAngle *= (4.0 * std::atan(1.0)) / 180.0; // convert back to radians
	
	//Snap the magnitude to an exponential filter
	float magnitude = this->joystick->GetMagnitude();
	//magnitude = std::pow(magnitude, 2.0);
	magnitude = std::pow(1.5,magnitude)-1;
	//Create a new axis based on the new angle and the magnitude of the previous axis vector	
	*xaxis = std::cos(snapAngle) * magnitude;
	*yaxis = std::sin(snapAngle) * magnitude;
}

void JoystickWrapper::GetRawAxis(float* xaxis, float* yaxis) const
{
	switch( this->type )
	{
	case Extreme3DPro:
		*xaxis = this->joystick->GetRawAxis(Joystick::kYAxis);
		*yaxis = this->joystick->GetRawAxis(Joystick::kZAxis);
		return;
	
	default:
		*xaxis = 0;
		*yaxis = 0;
		return;
	}
}

