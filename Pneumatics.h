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
};

class PneumaticSystem
{
public:
	PneumaticSystem(PneumaticsButtons buttons, Joystick *ds = 0);
	void setCompressor(bool a);
	bool isFullyPressurized();
	void start();
	void stop();
	
private:
	static int loop();
	
	static Solenoid *ballKicker;
	static Compressor *compressor;
	static Relay *relay;
	static DigitalInput *pressureSensor;
	
	Task* loopingTask;
	static Joystick *driveStick;
	
	static bool autocompressing;
	static PneumaticsButtons btns;
};

#endif
