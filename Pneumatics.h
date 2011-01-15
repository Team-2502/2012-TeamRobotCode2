#ifndef PNEUMATICS_H
#define PNEUMATICS_H

#include "WPILib.h"
class Compressor;
class DigitalInput;
class Solenoid;
class Relay;
class Joystick;

struct PneumaticsButtons {
	int kickButton;
	int manualButton;
	int autoButton;
	int liftButton;
};

class PneumaticSystem
{
public:
	PneumaticSystem(PneumaticsButtons buttons, Joystick *ds = 0);
	void setCompressor(bool a);
	bool isFullyPressurized();
	void start();
	void stop();
	static void kick();
	
private:
	static int loop();
	
	static Solenoid *ballKicker;
	static Solenoid *ballKicker2;
	static Solenoid *ballAntiKicker;
	static Solenoid *ballAntiKicker2;
	static Solenoid *lifter;
	static Compressor *compressor;
	static Relay *relay;
	static DigitalInput *pressureSensor;
	
	Task* loopingTask;
	static Joystick *driveStick;
	
	static bool lifting;
	static bool autocompressing;
	static bool twoSecondsUp;
	static PneumaticsButtons btns;
	
};

#endif
