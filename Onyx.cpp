#include <Dashboard.h>
#include "Onyx.h"
#include "Pneumatics.h"

Onyx::Onyx(void)
{
	dash->Printf("Initializing...");
	robotDrive = new RobotDrive(1,3,2,4);
	driveStick = new Joystick(1);
	PneumaticsButtons buttons;
	buttons.autoButton = 12;
	buttons.kickButton = 1;
	buttons.manualButton = 11;
	pSystem = new PneumaticSystem(buttons, driveStick);

	for (UINT8 t_buttonNum = 1; t_buttonNum <= NUM_JOYSTICK_BUTTONS; t_buttonNum++) {
		rightStickButtonState[t_buttonNum] = false;
		leftStickButtonState[t_buttonNum] = false;
		driveStickButtonState[t_buttonNum] = false;
	}
	dash->Printf("Initialized!");
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

void Onyx::TeleopPeriodic()
{
	GetWatchdog().Feed();
	driveStickX = driveStick->GetX();
	driveStickY = driveStick->GetY();
	robotDrive->SetLeftRightMotorSpeeds(driveStickY-driveStickX,driveStickX-driveStickY);
}

START_ROBOT_CLASS(Onyx);
