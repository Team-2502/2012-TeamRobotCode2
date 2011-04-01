#include "Arm.h"
#include "config.h"

Arm* Arm::instance = NULL;

Arm* Arm::GetInstance()
{
	if(!instance) {
		instance = new Arm;
	}
	return instance;
}

Arm::Arm()
{
	armJag = new Jaguar(WINCH_CHANNEL);
	armJag->SetSafetyEnabled(false);
	pidSource = new JagPIDSource(armJag);
	
	armPID = new PIDController(0.1,0.0,0.0,pidSource,armJag); //tune these.
	armPID->SetInputRange(-1.0,1.0);
	armPID->SetOutputRange(-1.0,1.0);
}

Arm::~Arm()
{
	delete armPID;
	delete pidSource;
	delete armJag;
	instance = NULL;
}

void Arm::setSpeed(float speed)
{
	armJag->SetSpeed(-1*speed);
}


