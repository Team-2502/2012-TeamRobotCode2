#ifndef ONYX_H
#define ONYX_H

#include <Dashboard.h>
#include "Pneumatics.h"
#include "WPILib.h"
#include "Output.h"
//#include "Vision.h"

class Onyx : public IterativeRobot
{
public:
	Onyx(void);
	void RobotInit(void);
	void DisabledInit(void);
	void AutonomousInit(void) {}
	void TeleopInit(void);

	void DisabledPeriodic(void) {}
	void AutonomousPeriodic(void);
	void TeleopPeriodic(void);

	void DisabledContinuous(void) {}
	void AutonomousContinuous(void) {}
	void TeleopContinuous(void) {}

private:
	static const int COMPUTATION = 400000000;
	static const int HZ = 10;
	static const int REP = 10;

	RobotDrive *robotDrive;
	Joystick *driveStick;
	DriverStationLCD *driverStationLCD;
	PneumaticSystem *pSystem;
//	Vision* visionSystem;


	float rightStickX;
	float rightStickY;
	float leftStickX;
	float leftStickY;
	float driveStickX;
	float driveStickY;
	float driveStickZ;

	bool kicking;
	int counter;
//	bool button12Held;
//	bool autocompress;
//	bool lifting;
	bool motors;
	bool lastStateMotor;
	int motorToggleButton;

	char* autocompressState;
	char* kickerState;
	char* pressureizationState;
	char* compressionState;
};

#endif
