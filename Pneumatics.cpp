#include <Task.h>
#include <Compressor.h>
#include "Output.h"
#include "Pneumatics.h"

//KICK_WAIT is in seconds.
#define KICK_WAIT 0.5

bool PneumaticSystem::autocompressing = false;
bool PneumaticSystem::lifting = false;
bool PneumaticSystem::twoSecondsUp = true;
Compressor* PneumaticSystem::compressor = new Compressor(4,1);
DigitalInput* PneumaticSystem::pressureSensor = new DigitalInput(4,9);
Solenoid* PneumaticSystem::ballAntiKicker = new Solenoid(8,1);
Solenoid* PneumaticSystem::ballAntiKicker2 = new Solenoid(8,2);
Solenoid* PneumaticSystem::ballKicker = new Solenoid(8,3);
Solenoid* PneumaticSystem::ballKicker2 = new Solenoid(8,4);
Solenoid* PneumaticSystem::lifter = new Solenoid(8,5);
Relay* PneumaticSystem::relay = new Relay(4,1,Relay::kForwardOnly);

Joystick* PneumaticSystem::driveStick = 0;
PneumaticsButtons PneumaticSystem::btns = {0,0,0};

PneumaticSystem::PneumaticSystem(PneumaticsButtons buttons, Joystick* js)
{
	driveStick = js;
	btns = buttons;
	autocompressing = false;
	ballKicker->Set(false);
	ballKicker2->Set(false);
	ballAntiKicker->Set(true);
	ballAntiKicker2->Set(true);
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
	ballKicker->Set(false);
	ballKicker2->Set(false);
	ballAntiKicker->Set(true);
	ballAntiKicker2->Set(true);
	lifter->Set(false);
	lifting = false;
	Output::setLifting(false);
	relay->Set(Relay::kOff);
	Output::setCompressing(false);
	autocompressing = false;
}

//Convenience function for determening pressurization of the system.
bool PneumaticSystem::isFullyPressurized()
{
	return !(pressureSensor->Get() == 0);
}

//Performs a ball-kick. Blocks thread from which it is called.
void PneumaticSystem::kick()
{
	if(!twoSecondsUp)
		return;
	Output::setWinching(true);
	relay->Set(Relay::kOff);
	ballAntiKicker->Set(false);
	ballAntiKicker2->Set(false);
	ballKicker->Set(true);
	ballKicker2->Set(true);
	Wait(KICK_WAIT);
	ballKicker2->Set(false);
	ballKicker->Set(false);
	ballAntiKicker->Set(true);
	ballAntiKicker2->Set(true);
	Output::setWinching(false);
}

int PneumaticSystem::loop()
{
	ballKicker->Set(false);
	ballKicker2->Set(false);
	ballAntiKicker->Set(true);
	ballAntiKicker2->Set(true);
	lifter->Set(false);
	lifting = false;
	Output::setLifting(false);
	bool fullyPressurized = false;
	bool lastStateAuto = driveStick->GetRawButton(btns.autoButton);
	bool lastStateKick = driveStick->GetRawButton(btns.kickButton);
	bool lastStateLift = driveStick->GetRawButton(btns.liftButton);
	Timer time;
	while(true)
	{
		if(time.Get() >= 2.0) {
			twoSecondsUp = true;
			time.Reset();
		}
//		fullyPressurized = !(pressureSensor->Get() == 0);
		Output::setFullyPressurized(fullyPressurized = !(pressureSensor->Get() == 0));
		//Controls compression depending on whether the autocompression feature is enabled.
		switch(autocompressing)
		{
		case true:
			if(fullyPressurized) {
				relay->Set(Relay::kOff);
				Output::setCompressing(false);
			} else {
				relay->Set(Relay::kOn);
				Output::setCompressing(true);
			}
			break;
		case false:
			if(driveStick->GetRawButton(btns.manualButton)) {
				if(!fullyPressurized || true) {
					autocompressing = false;
					relay->Set(Relay::kOn);
					Output::setCompressing(true);
					Output::setAutocompressing(autocompressing);
				}
			} else {
				relay->Set(Relay::kOff);
				Output::setCompressing(false);
			}
			break;
		default:
			break;
		}
		Output::setAutocompressing(autocompressing);
		
		//The following sections respond to Joystick input.
		//Performs a kick.
		if(driveStick->GetRawButton(btns.kickButton) && !lastStateKick && twoSecondsUp) {
			relay->Set(Relay::kOff);
			Output::setCompressing(false);
			kick();
			time.Start();
			twoSecondsUp = false;
		}
		//Toggles the arm.
		if(driveStick->GetRawButton(btns.liftButton) && !lastStateLift)
		{
			Output::setLifting(!lifting);
			lifter->Set(!lifting);
			lifting = !lifting;
		}
		//Toggles autocompression
		if(!driveStick->GetRawButton(btns.autoButton) && lastStateAuto) {
			autocompressing = !autocompressing;
			Output::setAutocompressing(autocompressing);
		}
		
		lastStateAuto = driveStick->GetRawButton(btns.autoButton);
		lastStateKick = driveStick->GetRawButton(btns.kickButton);
		lastStateLift = driveStick->GetRawButton(btns.liftButton);
		Wait(.01);
	}
	return 0;
}
