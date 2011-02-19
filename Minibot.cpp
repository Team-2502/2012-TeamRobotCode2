#include "Minibot.h"
#include "config.h"
#include "WPILib.h"

Minibot::Minibot()
{
	servo1 = new Servo(DIGITAL_SIDECAR_PORT,SERVO_CHANNEL_START);
	servo2 = new Servo(DIGITAL_SIDECAR_PORT,SERVO_CHANNEL_START+1);
	servo3 = new Servo(DIGITAL_SIDECAR_PORT,SERVO_CHANNEL_START+2);
	servo1->SetSafetyEnabled(false);
	servo2->SetSafetyEnabled(false);
	servo3->SetSafetyEnabled(false);
	deployed=false;
}

void Minibot::Deploy()
{
	servo1->Set(1);
	servo2->Set(1);
	servo3->Set(1);
	deployed=true;
}

void Minibot::StopDeploy()
{
	servo1->Set(0.0);
	servo2->Set(0.0);
	servo3->Set(0.0);
	deployed=false;
}

void Minibot::ToggleDeploy()
{
	servo1->Set(1-deployed);
	servo2->Set(1-deployed);
	servo3->Set(1-deployed);
	deployed=!deployed;
}
