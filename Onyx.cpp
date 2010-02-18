//2010
#include "Onyx.h"
#include "Pneumatics.h"
#include "Output.h"
#include "Vision.h"

Onyx::Onyx(void)
{
	lastStateMotor = true;
	motorsOn = false;
	Output::setMotors(false);
	robotDrive = new RobotDrive(4,1,3,2);
	driveStick = new Joystick(1);
	PneumaticsButtons buttons;
	buttons.autoButton = 12;
	buttons.kickButton = 1; //Trigger
	buttons.manualButton = 11;
	buttons.liftButton = 7;
	motorToggleButton = 8;
	pSystem = new PneumaticSystem(buttons, driveStick);
//	rangeFinder = new Ultrasonic(2,2);
	visionSystem = new Vision();
}

void Onyx::RobotInit()
{
	pSystem->start();
}

void Onyx::DisabledInit()
{
	pSystem->stop();
}

void Onyx::AutonomousInit()
{
	state = LocateBall;
	rangeFinder->SetAutomaticMode(true);
}

void Onyx::AutonomousPeriodic()
{
	GetWatchdog().Feed();
//	static unsigned int direction = 1;
//	switch(state)
//	{
//	case LocateBall:
//		robotDrive->Drive(0.3*(direction*2-1),0.0);
//		if(rangeFinder->GetRangeInches() <= 2)
//			state = KickBall;
//		else if(rangeFinder->GetRangeInches() <= 6)
//			state = TurnToBall;
//		break;
//	case TurnToBall:
//		if(direction&1) {
//			robotDrive->Drive(0.0,0.4); //left
//		} else {
//			robotDrive->Drive(0.0,-0.4); //right
//		}
//		Wait(0.2);
//		state=LocateBall;
//		break;
//	case KickBall:
//		PneumaticSystem::kick();
//		state = Done;
//		break;
//	case Done:
//	default:
//		direction = 1;
//		break;
//	}
}

void Onyx::TeleopInit()
{
	pSystem->start();
	robotDrive->SetInvertedMotor(robotDrive->kFrontRightMotor, true);
	robotDrive->SetInvertedMotor(robotDrive->kRearLeftMotor, true);
	robotDrive->SetInvertedMotor(robotDrive->kFrontLeftMotor, true);
	robotDrive->SetInvertedMotor(robotDrive->kRearRightMotor, true);
	visionSystem->startServer();
}

void Onyx::TeleopPeriodic()
{
	GetWatchdog().Feed();
	if(motorsOn)
	{
		robotDrive->ArcadeDrive(driveStick,false);
	}
	if(driveStick->GetRawButton(motorToggleButton) && !lastStateMotor && !motorsOn)
	{
		Output::setMotors(true);
		motorsOn = true;
	}
	else if(driveStick->GetRawButton(motorToggleButton) && !lastStateMotor && motorsOn)
	{
		Output::setMotors(false);
		motorsOn = false;
	}
	lastStateMotor = driveStick->GetRawButton(motorToggleButton);
}

START_ROBOT_CLASS(Onyx);
