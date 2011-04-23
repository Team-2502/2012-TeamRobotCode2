#include "LineListener.h"
#include "LineEvent.h"
#include "WPILib.h"
#include "config.h"
#include "DisplayWrapper.h"

LineListener::LineListener(EventDispatcher *e)
{
	parent = e;
	leftSensor   = new DigitalInput(LEFT_LINE_CHANNEL);
	rightSensor  = new DigitalInput(RIGHT_LINE_CHANNEL);
	centerSensor = new DigitalInput(CENTER_LINE_CHANNEL);
	leftState    = leftSensor->Get();
	rightState   = rightSensor->Get();
	centerState  = centerSensor->Get();
}

LineListener::~LineListener()
{
	delete leftSensor;
	delete rightSensor;
	delete centerSensor;
}

bool LineListener::update()
{
	bool leftValue   = leftSensor->Get();
	bool rightValue  = rightSensor->Get();
	bool centerValue = centerSensor->Get();
	if(leftValue != leftState || rightValue != rightState || centerValue != centerState)
	{
		int ret = 0;
		if(leftValue)
			ret |= LeftFork;
		if(rightValue)
			ret |= RightFork;
		if(centerValue)
			ret |= Forward;
		parent->sendEvent(new LineTrackingEvent(ret,this));
		DisplayWrapper::GetInstance()->PrintfLine(5,"Auto: LT: %i%i%i%i.",leftValue,centerValue,rightValue,ret);
		DisplayWrapper::GetInstance()->Output();
	}
	leftState    = leftSensor->Get();
	rightState   = rightSensor->Get();
	centerState  = centerSensor->Get();
	return true;
}
