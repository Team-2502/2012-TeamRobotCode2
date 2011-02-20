#include <math.h>
#include <Dashboard.h>
#include "WPILib.h"

#include "DisplayWrapper.h"
#include "DriverWrapper.h"
#include "JoystickWrapper.h"
#include "Arm.h"
#include "Vision/PCVideoServer.h"
#include "Minibot.h"

enum AutonomousState {
	TrackLine,
	PlaceTube,
	Prepare
};

class BetaRobot : public IterativeRobot
{
	public:
		BetaRobot(void);	
		void RobotInit(void) {}
		void DisabledInit(void) {pcvs->Stop();}
		void AutonomousInit(void) {}
		void TeleopInit(void);
		void AutonomousPeriodic(void);
		void TeleopPeriodic(void);
		void DisabledPeriodic(void) {}
		void DisabledContinuous(void) {}
		void AutonomousContinuous(void) {}
		void TeleopContinuous(void) {}
		
	private:
		JoystickWrapper* joystick;
		DriverWrapper* drive;
		Encoder* lift;
		Servo* servo;
		#ifdef USE_GYRO
		Gyro* gyro;
		#endif
		Arm *arm;
		PCVideoServer* pcvs;
		AutonomousState myState;
		Vision* eye;
		Minibot* mini;
		Timer* time;
		double shapeLockStart, triggerLockStart, miniStart, POVStart;
		bool triggerRelease, shapeRelease;
};

START_ROBOT_CLASS(BetaRobot);
