#include <Task.h>
#include <Compressor.h>
#include "Output.h"
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
	bool fullyPressurized = false;
	bool lastStateAuto = driveStick->GetRawButton(btns.autoButton);
	bool lastStateKick = driveStick->GetRawButton(btns.kickButton);
	while(true)
	{
		fullyPressurized = !(pressureSensor->Get() == 0);
		Output::setFullyPressurized(fullyPressurized);
		
		if(driveStick->GetRawButton(btns.autoButton) == false && lastStateAuto == true) {
			autocompressing = !autocompressing;
			Output::setAutocompressing(autocompressing);
		}
		if(driveStick->GetRawButton(btns.kickButton) == true && lastStateKick == false) {
			Output::setKicking(true);
			relay->Set(Relay::kOff);
			Output::setCompressing(false);
			ballKicker->Set(true);

			Wait(KICK_WAIT);

			ballKicker->Set(false);
			Output::setKicking(false);
		}
		if(driveStick->GetRawButton(btns.manualButton) == true) {
			autocompressing = false;
			relay->Set(Relay::kOn);
			Output::setCompressing(true);
			Output::setAutocompressing(autocompressing);
		} else {
			relay->Set(Relay::kOff);
			Output::setCompressing(false);
		}
		if(autocompressing)
		{
			if(fullyPressurized) {
				relay->Set(Relay::kOff);
				Output::setCompressing(false);
			} else {
				relay->Set(Relay::kOn);
				Output::setCompressing(true);
			}
		}
		lastStateAuto = driveStick->GetRawButton(btns.autoButton);
		lastStateKick = driveStick->GetRawButton(btns.kickButton);
		Wait(.01);
	}
	return 0;
}
