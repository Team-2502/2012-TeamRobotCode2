#include "GyroListener.h"
#include "GyroAngleEvent.h"
#include "WPILib.h"
#include "config.h"

GyroListener::GyroListener(EventDispatcher *e)
{
	parent = e;
	gyro = new Gyro(GYRO_SLOT,GYRO_CHANNEL);
	lastAngle = gyro->GetAngle();
}

GyroListener::~GyroListener()
{
	delete gyro;
}

bool GyroListener::update()
{
	if(lastAngle != gyro->GetAngle())
	{
		parent->sendEvent(new GyroAngleEvent(GYRO_MULT*gyro->GetAngle(),this));
	}
	return true;
}
