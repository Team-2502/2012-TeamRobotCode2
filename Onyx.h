#ifndef ONYX_H
#define ONYX_H

#include <Dashboard.h>
#include "Pneumatics.h"
#include "WPILib.h"
#include "Output.h"
#include "Vision.h"

class Onyx : public IterativeRobot
{
public:
	Onyx(void);
	void RobotInit(void);
	void DisabledInit(void);
	void AutonomousInit(void);
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
	Ultrasonic *rangeFinder;
	Vision* visionSystem;
	
	enum { LocateBall, TurnToBall, KickBall, Done } state;

	bool motorsOn;
	bool lastStateMotor;
	int motorToggleButton;
};

#endif
