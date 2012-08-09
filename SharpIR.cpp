#include <WPILib.h>
#include "SharpIR.h"

SharpIR::SharpIR(UINT8 moduleNumber, UINT32 channel, double signalVoltage, unsigned signalToggleCount ) :
	AnalogChannel(moduleNumber, channel)
{
	this->signalVoltage = signalVoltage;
	this->signalToggleCount = signalToggleCount;
	currentCount = 0;
}

bool SharpIR::Get() 
{ 
	if( GetVoltage() > signalVoltage )
	{
		currentCount++;
		return currentCount > signalToggleCount;
	}
	else
	{
		currentCount = 0;
		return false;
	}
}
