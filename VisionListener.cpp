#include "VisionListener.h"
#include "VisionRoutines.h"
#include "VisionEvent.h"

VisionListener::VisionListener(EventDispatcher* e)
{
	vis = Vision::GetInstance();
	parent = e;
	lastReport = vis->getNearestPeg();
}

VisionListener::~VisionListener()
{
	delete vis;
}

bool VisionListener::update()
{
	TargetReport rpt = vis->getNearestPeg();
	if(rpt.area != lastReport.area || rpt.region != lastReport.region)
	{
		lastReport = rpt;
		parent->sendEvent(new VisionEvent(rpt,this));
	}
	return true;
}
