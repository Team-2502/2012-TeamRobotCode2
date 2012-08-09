#ifndef SHARPIR_H
#define SHARPIR_H

#include <WPILib.h>

class SharpIR : public AnalogChannel
{
public:
	SharpIR(UINT8 moduleNumber, UINT32 channel, double signalVoltage, unsigned signalToggleCount );
	bool Get();

private:
	double signalVoltage;
	unsigned signalToggleCount;
	unsigned currentCount;
};

#endif
