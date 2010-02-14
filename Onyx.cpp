//2010
#include "Onyx.h"
#include "Pneumatics.h"
#include "Output.h"
//#include "Vision.h"

Onyx::Onyx(void)
{
	lastStateMotor = true;
	motors = false;
	Output::setMotors(false);
	robotDrive = new RobotDrive(4,1,3,2);
	driveStick = new Joystick(1);
	PneumaticsButtons buttons;
	buttons.autoButton = 12;
	buttons.kickButton = 1;
	buttons.manualButton = 11;
	buttons.liftButton = 7;
	motorToggleButton = 8;
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
	if(motors)
	{
		robotDrive->ArcadeDrive(driveStick,false);
	}
	if(driveStick->GetRawButton(motorToggleButton)&&lastStateMotor== false&&motors==false)
	{
		Output::setMotors(true);
		motors = true;
	}
	else if(driveStick->GetRawButton(motorToggleButton)&&lastStateMotor== false&&motors==true)
	{
		Output::setMotors(false);
		motors = false;
	}
//	driveStickX = driveStick->GetX();
//	driveStickY = driveStick->GetY();
//	robotDrive->SetLeftRightMotorSpeeds((driveStickY-driveStickX),(driveStickX-driveStickY));
	lastStateMotor = driveStick->GetRawButton(motorToggleButton);
}

START_ROBOT_CLASS(Onyx);
