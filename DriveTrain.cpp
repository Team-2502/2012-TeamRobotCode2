#include <cmath>

#include <WPILib.h>

#include "Constants.h"
#include "DisplayWriter.h"
#include "DriveTrain.h"
#include "Math.h"
#include "Logger.h"
#include "Singleton.h"

DriveTrain::DriveTrain()
{
	enabled = true;
	
	Singleton<Logger>::GetInstance().Logf("DriveTrain() initializing.");

	this->left = new Jaguar(1, 1);
	this->right = new Jaguar(1, 2);

	this->left->SetSafetyEnabled(false);
	this->right->SetSafetyEnabled(false);
}

DriveTrain::~DriveTrain()
{
	LOGGER.Logf("~DriveTrain() stopping.");

	delete this->left;
	delete this->right;
}

void DriveTrain::DriveArcade(double twist, double speed)
{
	if(!enabled) {
		twist = 0.0;
		speed = 0.0;
	}
	twist *= -1.0;
	speed *= -1.0;
	left->Set(-1.0 * speed + twist);
	right->Set(speed + twist);
}

void DriveTrain::DriveTank(double leftChannel, double rightChannel)
{
	if(!enabled) {
		leftChannel = 0.0;
		rightChannel = 0.0;
	}
	left->Set(-1.0 * leftChannel);
	right->Set(-1.0 * rightChannel);
}

void DriveTrain::ReservePrimaryLines()
{
	primaryDisplay.Reserve(0); 
}

void DriveTrain::ReserveSecondaryLines()
{
	secondaryDisplay.Reserve(0);
}

void DriveTrain::SetLeft(double value) 
{
	if(!enabled) {
		value = 0.0;
	}
	left->Set(value);
}

void DriveTrain::SetRight(double value) 
{
	if(!enabled) {
		value = 0.0;
	}
	right->Set(value);
}
