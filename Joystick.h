#ifndef JOYSTICK_H
#define JOYSTICK_H

#include "WPILib.h"
class Joystick_Wrapper {
public:
	Joystick_Wrapper(int port);
	double getX();
	double getY();
	double getMagnitude();
	double getAngle();
	double getTwist();
	double getThrottle();
	double getPOV();
	bool getTrigger();
	bool getShapeSwitch();
	int getLevelButtons();
	//typedef enum {extreme3DPro,attack3} StickType;
private:
	Joystick* stick
};