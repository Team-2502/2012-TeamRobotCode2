#include <math.h>
#include "JoystickWrapper.h"
#include "config.h"
using namespace std;

JoystickWrapper::JoystickWrapper(int port, StickType type)
{
	//Initialize stuff
	this->joystick = new Joystick(port);
	
	this->type = type;
	SetSnapPoints(8);
}

JoystickWrapper::~JoystickWrapper()
{
	delete joystick;
}

float JoystickWrapper::GetAngle() const
{
	float x, y;
	GetRawAxis(&x, &y);
	return (180.0 / acos(-1.0)) * atan2(x, -1.0 * y);
}

float JoystickWrapper::GetMagnitude() const
{
	float x, y;
	GetRawAxis(&x, &y);
	return sqrt(pow(x, 2.0) + pow(y, 2.0));
}

void JoystickWrapper::GetPov(float* x, float* y) const
{
	switch( this->type )
	{
	case Extreme3DPro:
		*x = this->joystick->GetRawAxis(5);
		*y = -1.0 * this->joystick->GetRawAxis(6);
		return;
		
	default:
		*x = 0.0;
		*y = 0.0;
		return;
	}
}

int JoystickWrapper::GetPovAngle() const
{
	float x, y;
	GetPov(&x, &y);
	int a = (int)x;
	int b = (int)y;
	switch(a)
	{
	case -1:
		switch(b)
		{
		case -1:
			return SOUTHWEST;
		case 0:
			return WEST;
		case 1:
			return NORTHWEST;
		}
	case 0:
		switch(b)
		{
		case -1:
			return SOUTH;
		case 1:
			return NORTH;
		}
	case 1:
		switch(b)
		{
		case -1:
			return SOUTHEAST;
		case 0:
			return EAST;
		case 1:
			return NORTHEAST;
		}
	}
	
	return 0;
}

void JoystickWrapper::GetAxis(float* xaxis, float* yaxis) const
{
	float angle = GetAngle();
	
	//Calculate the angle that we will snap to:
	float snapAngle = floor((angle / 360.0) * (float)this->snapPoints) * (360.0 / (float)this->snapPoints);
	snapAngle += 360.0 / (2.0 * (float)this->snapPoints);
	if( snapAngle > 360.0 )
		snapAngle -= 360.0;
	snapAngle *= (4.0 * atan(1.0)) / 180.0; // convert back to radians
	
	//Snap the magnitude to an exponential filter
	float magnitude = this->joystick->GetMagnitude();
	magnitude = pow(2.0,magnitude)-1;
	//Create a new axis based on the new angle and the magnitude of the previous axis vector	
	*xaxis = cos(snapAngle) * magnitude;
	*yaxis = sin(snapAngle) * magnitude;
}

void JoystickWrapper::GetRawAxis(float* xaxis, float* yaxis) const
{
	*xaxis = this->joystick->GetRawAxis(Joystick::kDefaultXAxis);
	*yaxis = /*-1.0 * */this->joystick->GetRawAxis(Joystick::kDefaultYAxis);
}

float JoystickWrapper::GetRotation() const
{
	switch( this->type )
	{
	case Extreme3DPro:
	case DualAction:
		return this->joystick->GetRawAxis(Joystick::kDefaultZAxis);
		
	case Attack3:
	default:
		return 0.0;
	}
}

float JoystickWrapper::GetThrottle() const
{
	switch( this->type )
	{
	case Extreme3DPro:
		return -1.0 * this->joystick->GetRawAxis(Joystick::kDefaultTwistAxis);
		
	case Attack3:
		return -1.0 * this->joystick->GetRawAxis(Joystick::kDefaultZAxis);
		
	case DualAction:
	default:
		return 0.0;
	}
}
