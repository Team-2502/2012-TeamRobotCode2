#include <Task.h>
#include <Compressor.h>
#include "Pneumatics.h"

#define KICK_WAIT 0.5

bool PneumaticSystem::autocompressing = false;
Compressor* PneumaticSystem::compressor = new Compressor(4,1);
DigitalInput* PneumaticSystem::pressureSensor = new DigitalInput(4,1);
Solenoid* PneumaticSystem::ballKicker = new Solenoid(8,1);
Relay* PneumaticSystem::relay = new Relay(1,Relay::kForwardOnly);
Joystick* PneumaticSystem::ds = 0;
PneumaticsButtons PneumaticSystem::btns = {0,0,0};

PneumaticSystem::PneumaticSystem(PneumaticsButtons buttons, Joystick* js)
{
	ds = js;
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
	bool lastState = ds->GetRawButton(btns.autoButton);
	bool lastStateKick = ds->GetRawButton(btns.kickButton);
	bool lastStateManual = ds->GetRawButton(btns.manualButton);
	while(true)
	{
		if(ds->GetRawButton(btns.autoButton) == false && lastState == true) {
			autocompressing = !autocompressing;
		}
		if(ds->GetRawButton(btns.kickButton) == true && lastStateKick == false) {
			ballKicker->Set(true);
			Wait(KICK_WAIT);
			ballKicker->Set(false);
		}
		if(ds->GetRawButton(btns.manualButton) && !lastStateManual) {
			autocompressing = false;
			lastStateManual = true;
			relay->Set(Relay::kOn);
		} else {
			lastStateManual = false;
			relay->Set(Relay::kOff);
		}
		if(autocompressing)
		{
			if(pressureSensor->Get())
				relay->Set(Relay::kOff);
			else
				relay->Set(Relay::kOn);
		}
		lastState = ds->GetRawButton(btns.autoButton);
		lastStateKick = ds->GetRawButton(btns.kickButton);
		Wait(.01);
	}
	return 0;
}
