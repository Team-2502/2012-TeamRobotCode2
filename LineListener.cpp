#include "LineListener.h"
#include "LineEvent.h"
#include "WPILib.h"
#include "config.h"

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
	int leftValue = leftSensor->Get() ? 1 : 0; int oldLeftValue = leftState ? 1 : 0;
	int rightValue = rightSensor->Get() ? 1 : 0; int oldRightValue = rightState ? 1 : 0;
	int centerValue = centerSensor->Get() ? 1 : 0; int oldCenterValue = centerState ? 1 : 0;
	if(leftValue != oldLeftValue || rightValue != oldRightValue || centerValue != oldCenterValue)
	{
		parent->sendEvent(new LineTrackingEvent(LeftFork*leftValue+Forward*rightValue+RightFork*rightValue,this));
	}
	return true;
}
