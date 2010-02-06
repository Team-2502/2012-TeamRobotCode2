#include <Task.h>
#include <Compressor.h>
#include "Pneumatics.h"

#define KICK_WAIT 0.5

bool PneumaticSystem::autocompressing = false;
Compressor* PneumaticSystem::compressor = new Compressor(4,1);
DigitalInput* PneumaticSystem::pressureSensor = new DigitalInput(4,1);
Solenoid* PneumaticSystem::ballKicker = new Solenoid(8,1);
Relay* PneumaticSystem::relay = new Relay(1,Relay::kForwardOnly);
Joystick* PneumaticSystem::driveStick = 0;
PneumaticsButtons PneumaticSystem::btns = {0,0,0};

PneumaticSystem::PneumaticSystem(PneumaticsButtons buttons, Joystick* js)
{
	driveStick = js;
	btns = buttons;
	autocompressing = false;
	ballKicker->Set(false);
	compressor->Start();
	loopingTask = new Task("2502Pn", (FUNCPTR) loop);
}

void PneumaticSystem::start()
{
	loopingTask->Start();
}

void PneumaticSystem::stop()
{
	loopingTask->Stop();
}

bool PneumaticSystem::isFullyPressurized()
{
	return !(pressureSensor->Get() == 0);
}

int PneumaticSystem::loop()
{
	bool lastStateAuto = driveStick->GetRawButton(btns.autoButton);
	bool lastStateKick = driveStick->GetRawButton(btns.kickButton);
	while(true)
	{
		if(driveStick->GetRawButton(btns.autoButton) == false && lastStateAuto == true) {
			autocompressing = !autocompressing;
		}
		if(driveStick->GetRawButton(btns.kickButton) == true && lastStateKick == false) {
			relay->Set(Relay::kOff);
			ballKicker->Set(true);
			Wait(KICK_WAIT);
			ballKicker->Set(false);
		}
		if(driveStick->GetRawButton(btns.manualButton) == true) {
			autocompressing = false;
			relay->Set(Relay::kOn);
		} else {
			relay->Set(Relay::kOff);
		}
		if(autocompressing)
		{
			if(pressureSensor->Get())
				relay->Set(Relay::kOff);
			else
				relay->Set(Relay::kOn);
		}
		lastStateAuto = driveStick->GetRawButton(btns.autoButton);
		lastStateKick = driveStick->GetRawButton(btns.kickButton);
		Wait(.01);
	}
	return 0;
}
