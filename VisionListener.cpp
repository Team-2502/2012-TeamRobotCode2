#include "VisionListener.h"
#include "VisionRoutines.h"
#include "VisionEvent.h"

EventDispatcher* VisionListener::parent = NULL;

VisionListener::VisionListener(EventDispatcher* e)
{
	visionTask = new Task("2502Vn",(FUNCPTR)loop);
	parent = e;
}

VisionListener::~VisionListener()
{
	visionTask->Stop();
	delete visionTask;
}

void VisionListener::start()
{
	if(parent)
		visionTask->Start();
}

void VisionListener::stop()
{
	visionTask->Stop();
}

void VisionListener::loop()
{
	TargetReport lastReport = Vision::GetInstance()->getNearestPeg();
	while(parent)
	{
		TargetReport rpt = Vision::GetInstance()->getNearestPeg();
		if(rpt.area != lastReport.area || rpt.x != lastReport.x || rpt.y != lastReport.y)
		{
			lastReport = rpt;
			parent->sendEvent(new VisionEvent(rpt,0));
		}
		Wait(0.03);
	}
}
