#include <Task.h>
#include <Compressor.h>
#include "Pneumatics.h"

#define KICK_WAIT 0.5

PneumaticSystem::PneumaticSystem(PneumaticsButtons buttons, Joystick* js)
{
	ds = js;
	btns = buttons;
	autocompressing = false;

	relay = new Relay(1);
	pressureSensor = new DigitalInput(4,1);
	ballKicker = new Solenoid(8,1);
	compressor = new Compressor(4,1);
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
	bool lastState = ds->GetRawButton(btns.autoButton);
	bool lastStateKick = ds->GetRawButton(btns.kickButton);
	while(true)
	{
		if(ds->GetRawButton(btns.autoButton) == false && lastState == true) {
			autocompressing = !autocompressing;
		}
		if(ds->GetRawButton(btns.kickButton) == false && lastStateKick == true) {
			ballKicker->Set(true);
			Wait(KICK_WAIT);
			ballKicker->Set(false);
		}
		if(ds->GetRawButton(btns.manualButton)) {
			autocompressing = false;
			relay->Set(Relay::kOn);
		} else {
			relay->Set(Relay::kOff);
		}
		if(autocompressing)
		{
			if(pressureSensor->Get())
				relay->Set(Relay::kOn);
			else
				relay->Set(Relay::kOff);
		}
		lastState = ds->GetRawButton(btns.autoButton);
		lastStateKick = ds->GetRawButton(btns.kickButton);
		Wait(.01);
	}
	return 0;
}
