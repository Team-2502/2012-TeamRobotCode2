//2010
#include "Onyx.h"
#include "Pneumatics.h"
//#include "Vision.h"

Onyx::Onyx(void)
{
	robotDrive = new RobotDrive(4,1,3,2);
	driveStick = new Joystick(1);
	PneumaticsButtons buttons;
	buttons.autoButton = 12;
	buttons.kickButton = 1;
	buttons.manualButton = 11;
	pSystem = new PneumaticSystem(buttons, driveStick);
//	visionSystem = new Vision();
}

void Onyx::RobotInit()
{
	pSystem->start();
}

void Onyx::DisabledInit()
{
	pSystem->stop();
}

void Onyx::AutonomousPeriodic()
{
	GetWatchdog().Feed();
}

void Onyx::TeleopInit()
{
	pSystem->start();
	robotDrive->SetInvertedMotor(robotDrive->kFrontRightMotor, true);
	robotDrive->SetInvertedMotor(robotDrive->kRearLeftMotor, true);
	robotDrive->SetInvertedMotor(robotDrive->kFrontLeftMotor, true);
	robotDrive->SetInvertedMotor(robotDrive->kRearRightMotor, true);
//	visionSystem->start();
}

void Onyx::TeleopPeriodic()
{
	GetWatchdog().Feed();
	robotDrive->ArcadeDrive(driveStick,false);
//	driveStickX = driveStick->GetX();
//	driveStickY = driveStick->GetY();
//	robotDrive->SetLeftRightMotorSpeeds((driveStickY-driveStickX),(driveStickX-driveStickY));
}

START_ROBOT_CLASS(Onyx);
