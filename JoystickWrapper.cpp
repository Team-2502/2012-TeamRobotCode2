#include "JoystickWrapper.h"
#include "Math.h"

using namespace std;

JoystickWrapper::JoystickWrapper(int port, StickType type)
{
	this->joystick = new Joystick(port);
	this->type = type;
	SetSnapPoints(8);
}

JoystickWrapper::~JoystickWrapper()
{
	delete joystick; joystick = 0;
}

float JoystickWrapper::GetAngle() const
{
	float x, y;
	GetRawAxis(&x, &y);
	return ((180.0 / 4 / atan(1.0)) * atan2(x, -1.0 * y)) + 180.0;
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
	//float angle = GetAngle();

	//Calculate the angle that we will snap to:
	//angle = floor(angle/(360/snapPoints))*(360/snapPoints) * PI / 180;

	//Snap the magnitude to an exponential filter
	//float magnitude = this->joystick->GetMagnitude();
	//magnitude = (pow(MAG_EXPONENTIAL,magnitude)-1)/(MAG_EXPONENTIAL-1);

	//Create a new axis based on the new angle and the magnitude of the previous axis vector	
	//*xaxis = cos(angle) * magnitude;
	//*yaxis = sin(angle) * magnitude;
	
	GetRawAxis(xaxis,yaxis);

	//*xaxis = ((*xaxis < 0.0) ? -1.0 : 1.0) * (exp(fabs(*xaxis))-1)/(exp(1)-1.0);
	//*yaxis = ((*yaxis < 0.0) ? -1.0 : 1.0) * (exp(fabs(*yaxis))-1)/(exp(1)-1.0);
}

void JoystickWrapper::GetRawAxis(float* xaxis, float* yaxis) const
{
	*xaxis = this->joystick->GetRawAxis(Joystick::kDefaultXAxis);
	*yaxis = -this->joystick->GetRawAxis(Joystick::kDefaultYAxis);
}

float JoystickWrapper::GetRotation() const
{
	float r = GetRawRotation();
	return r*r*r;
}

float JoystickWrapper::GetRawRotation() const
{
	switch(this->type)
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
	switch(this->type)
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

/*
 * Josh: Created the GetButton function
 * Thought'd be useful
 */
bool JoystickWrapper::GetButton(int buttonID)
{
	return joystick->GetRawButton(buttonID);
}
