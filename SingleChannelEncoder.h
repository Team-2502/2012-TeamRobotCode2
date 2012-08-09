#ifndef SINGLECHANNELENCODER_H
#define SINGLECHANNELENCODER_H

#include <WPILib.h>

class SingleChannelEncoder : public Counter, public PIDSource
{
public:
	SingleChannelEncoder(UINT32 channel, SpeedController& controller);
	~SingleChannelEncoder();
	
	double GetRate() const;
	double PIDGet();
	
private:
	double rate;
	SpeedController& controller;
	Timer* timer;
};

#endif // SINGLECHANNELENCODER_H
