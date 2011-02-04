#include <Joystick.h>
#include "WPILib.h"
#include <cmath>

Joystick_Wrapper::Joystick_Wrapper(int port) {
	stick = new Joystick(port);
}
double Joystick_Wrapper::getX() {
	//WPILib interprets the x-axis as the y-axis
	return stick->GetAxis(kYAxis);
}
double Joystick_Wrapper::getY() {
	//WPILib interprets the y-axis as the z-axis
	return stick->GetAxis(kZAxis);
}
double Joystick_Wrapper::getMagnitude() {
	return sqrt(getX()*getX()+getY()*getY());
}
double Joystick_Wrapper::getAngle() {
	return (180/acos(-1))*atan2(getX(), -getY());
}
double Joystick_Wrapper::getTwist() {
	return stick->GetAxis(kTwistAxis);
}
double Joystick_Wrapper::getThrottle() {
	return stick->GetAxis(kThrottleAxis);
}
double Joystick_Wrapper::getPOV() {
	return stick->GetAxis(5);
}
bool Joystick_Wrapper::getTrigger() {
	return getTrigger();
}
bool Joystick_Wrapper::getShapeSwitch() {
	return getTop();
}
int Joystick_Wrapper::getLevelButtons();

