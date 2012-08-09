#include "Math.h"
#include "SingleChannelEncoder.h"

SingleChannelEncoder::SingleChannelEncoder(UINT32 channel, SpeedController& controller) :
		Counter(channel),
		rate(0.0),
		controller(controller)
{
	timer = new Timer();
	timer->Start();
}

SingleChannelEncoder::~SingleChannelEncoder()
{
	delete timer;
}

double SingleChannelEncoder::GetRate() const
{
	return rate;
}

double SingleChannelEncoder::PIDGet()
{
	rate = ((double)Get() / 128.0) / timer->Get();
	Reset();
	timer->Reset();
	return rate * (controller.Get() > 0 ? 1.0 : -1.0);
}
