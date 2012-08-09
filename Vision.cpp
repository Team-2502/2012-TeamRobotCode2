#include <WPILib.h>
#include "nivision.h"
#include <cmath>
#include "Math.h"
#include <stdio.h>

#include "Constants.h"
#include "DisplayWriter.h"
#include "Singleton.h"
#include "Vision.h"
#include <fstream>

bool Vision::enabled = true;
AxisCamera *Vision::cam= NULL;
VisionSpecifics *Vision::engine= NULL;
int Vision::bestTargetCount = 0;
vector<TargetReport> Vision::bestTargets = vector<TargetReport>();

void Vision::reservePrimaryLines() { primaryDisplay.Reserve(1); }
void Vision::reserveSecondaryLines() { secondaryDisplay.Reserve(5); }


/**
 * Get a distance given a known height of an object in an image.
 * 
 * \param realHeight the actual height of the object.
 * \param imageHeight the height of the object in pixels.
 * \return the distance to the object.
 */
static double GetDistanceFromHeight(double realHeight, double imageHeight)
{
	return (2*240.0/2.0)/tan(degToRad(17.0965405)) / (imageHeight * 2.0 / realHeight);
}

Vision::Vision(VisionSpecifics *backend)
{
	engine = backend;
	cam = &AxisCamera::GetInstance("10.25.2.11");
	cam->WriteResolution(AxisCamera::kResolution_320x240);
	visionTask = new Task("2502Vn",(FUNCPTR)loop);
}

Vision::~Vision()
{
	delete engine;
	visionTask->Stop();
	delete visionTask;
}

void Vision::start()
{
	visionTask->Start();
}

void Vision::stop()
{
	visionTask->Stop();
}

void Vision::loop()
{
	while (true)
	{
		HSLImage* cap = new HSLImage;
		if(enabled) 
		{
			cam->GetImage(cap);
			engine->GetBestTargets(cap, bestTargets, bestTargetCount);
			VISION.primaryDisplay.PrintfLine(0, "Vis #:%d Dist:%f H:%f", bestTargetCount, bestTargets[0].distance, bestTargets[0].height);
		}
		delete cap;
		Wait(0.01);
	}
}

bool Vision::isHorizontallyAligned(TargetReport &targets1, TargetReport &targets2)
{
	return (fabs(targets1.centerX - targets2.centerX) <= (targets1.width + targets2.width) / 2 * 0.4);
}

bool Vision::isVerticallyAligned(TargetReport &targets1, TargetReport &targets2)
{
	return (fabs(targets1.centerY - targets2.centerY) <= (targets1.height + targets2.height) / 2 * 0.75);
}

bool Vision::isBottomTarget( TargetReport &target )
{
	return (target.normalizedY > 0.0);
}

void Vision::GetTargetCase(vector <TargetReport> &targets, int numtargets, int& top, int& left, int& right, int& bottom)
{
	top = -1;
	left = -1;
	right = -1;
	bottom = -1;

	
	// one target
	if( numtargets == 1 )
	{
		if ( isBottomTarget( targets[0] ))
			bottom = 0;
		return;
	}

	// two targets
	if( numtargets == 2 )
	{
		// top and bottom?
		if( isHorizontallyAligned( targets[0], targets[1] ))
		{
			if( isBottomTarget( targets[0] ))
			{
				bottom = 0;
				top = 1;
			}
			else
			{
				top = 0;
				bottom = 1;
			}
			return;
		}

		// left and right?
		if( isVerticallyAligned( targets[0], targets[1] ))
		{
			if( targets[0].centerX < targets[1].centerX )
			{
				left = 0;
				right = 1;
			}
			else
			{
				right = 0;
				left = 1;
			}
			return;
		}

		// diagonal targets
		// Are either of them the bottom target?
		if( isBottomTarget( targets[0] ) || isBottomTarget( targets[1] ))
		{
			if( isBottomTarget( targets[0] ))
			{
				bottom = 0;
				// bottom/right?
				if (targets[1].centerX > targets[0].centerX )
					right = 1;
				else
					left = 1;
				return;
			}
			else
			{
				bottom = 1;
				// bottom/right?
				if (targets[0].centerX > targets[1].centerX )
					right = 0;
				else
					left = 0;
				return;
			}
		}
		else
		{
			// first one top?
			if( targets[0].centerY > targets[1].centerY )
			{
				top = 1;
				// top/right?
				if (targets[1].centerX < targets[0].centerX )
					right = 0;
				else
					left = 0;
				return;
			}
			else
			{
				top = 0;
				// bottom/right?
				if (targets[0].centerX < targets[1].centerX )
					right = 1;
				else
					left = 1;
				return;
			}
		}
	}
	
	TargetPair hor;
	hor.set = false;
	hor.a = -1;
	hor.b = -1;
	TargetPair ver;
	ver.set = false;
	ver.a = -1;
	ver.b = -1;
	bool viable = true;

	for (int a = 0; a < numtargets-1; a++)
	{
		for (int b = a+1; b < numtargets; b++)
		{
			// Check for X Similarities
			if (isHorizontallyAligned(targets[a], targets[b]))
			{
				if (ver.set == false)
				{
					ver.a = a;
					ver.b = b;
					ver.set = true;
				}
				else
				{
					viable = false; // Duplicate pairs of similar X Values
				}
			}
			// Check for Y Similarities
			if (isVerticallyAligned(targets[a], targets[b]))
			{
				if (hor.set == false)
				{
					hor.a = a;
					hor.b = b;
					hor.set = true;
				}
				else
				{
					viable = false; // Duplicate pairs of similar Y Values
				}
			}
		}
	}
	// Left and Right targets - Determined by y values
	if (hor.set == true && viable == true)
	{
		if (targets[hor.a].centerX < targets[hor.b].centerX)
		{
			left = hor.a;
			right = hor.b;
		}
		else
		{
			right = hor.a;
			left = hor.b;
		}
		for (int i = 0; i < numtargets; i++)
		{
			if (i == hor.a || i == hor.b)
				continue;
			if (targets[i].centerY < targets[hor.a].centerY)
			{
				if (fabs(targets[i].centerX - (targets[hor.a].centerX + targets[hor.b].centerX) / 2) <= targets[i].width * 0.4)
				{
					top = i;
				}
			}
			else if (targets[i].centerY > targets[hor.a].centerY)
			{
				if (fabs(targets[i].centerX - (targets[hor.a].centerX + targets[hor.b].centerX) / 2) <= targets[i].width * 0.4)
				{
					bottom = i;
				}
			}
		}
	}
	// Top and Bottom targets - Determined by x values
	if (ver.set == true && viable == true)
	{
		if (targets[ver.a].centerY < targets[ver.b].centerY)
		{
			top = ver.a;
			bottom = ver.b;
		}
		else
		{
			bottom = ver.a;
			top = ver.b;
		}
		for (int i = 0; i < numtargets; i++)
		{
			if (i == ver.a || i == ver.b)
				continue;
			if (targets[i].centerX < targets[ver.a].centerX)
			{
				if (fabs(targets[i].centerY - (targets[ver.a].centerY + targets[ver.b].centerY) / 2) <= targets[i].height)
				{
					left = i;
				}
			}
			else if (targets[i].centerX > targets[ver.a].centerX)
			{
				if (fabs(targets[i].centerY - (targets[ver.a].centerY + targets[ver.b].centerY) / 2) <= targets[i].height)
				{
					right = i;
				}
			}
		}
	}
	/*
	if (top == -1 && (left == -1 || right == -1))
	{
		for (int a = 0; a < numtargets-1; a++)
		{
			for (int b = a+1; b < numtargets; b++)
			{
				// Checking for top target
				if (targets[a].normalizedY < 0)
				{
					// Checking for a center target (a is top, b is center)
					if (targets[b].centerY > targets[a].centerY)
					{
						if (fabs((targets[b].x + targets[b].width) - targets[a].x) <= targets[a].width * 0.2)
						{
							if (targets[b].x < targets[a].x)
							{
								top = a;
								left = b;
							}
							else
							{
								top = a;
								right = b;
							}
						}
					}
				}
				else if (targets[b].normalizedY < 0)
				{
					// Checking for a center target (b is top, a is center)
					if (targets[a].centerY > targets[b].centerY)
					{
						if (fabs((targets[b].x + targets[b].width) - targets[a].x) <= targets[a].width * 0.2)
						{
							if (targets[b].x < targets[a].x)
							{
								top = b;
								left = a;
							}
							else
							{
								top = b;
								right = a;
							}
						}
					}
				}
			}
		}
	}
	*/
}

void Vision::FindTarget(double& offset, double& distance)
{
	distance = 0.0;
	offset = 0.0;

	TargetReport tmp = GetBestTarget();
	if (tmp.normalizedY > 0.0)
	{
		distance = tmp.distance;
		offset = tmp.normalizedX;
	}

	if (bestTargetCount == 0)
		return;
	int targetCase[4] = { -1, -1, -1, -1 };
	GetTargetCase(bestTargets, bestTargetCount, targetCase[TOP_TARGET], targetCase[LEFT_TARGET], targetCase[RIGHT_TARGET], targetCase[BOTTOM_TARGET]);
	
	secondaryDisplay.PrintfLine(0, "Top Target: %d", targetCase[TOP_TARGET]);
	secondaryDisplay.PrintfLine(1, "Left Target: %d", targetCase[LEFT_TARGET]);
	secondaryDisplay.PrintfLine(2, "Right Target: %d", targetCase[RIGHT_TARGET]);
	secondaryDisplay.PrintfLine(3, "Bottom Target: %d", targetCase[BOTTOM_TARGET]);
	// Handle target cases

	if (targetCase[TOP_TARGET] >= 0 && targetCase[BOTTOM_TARGET] >= 0)
	{
		//Top / Bottom (best case scenario)
		offset = bestTargets[TOP_TARGET].normalizedX;

		double realHeight = BASKET_TOP_ELEVATION - BASKET_BOTTOM_ELEVATION;
		distance = GetDistanceFromHeight(realHeight, fabs(bestTargets[targetCase[BOTTOM_TARGET]].centerY - bestTargets[targetCase[TOP_TARGET]].centerY));
	}
	else if (targetCase[TOP_TARGET] >= 0 && (targetCase[LEFT_TARGET] >= 0 || targetCase[RIGHT_TARGET] >= 0))
	{
		//One of the top diagonals
		offset = bestTargets[targetCase[TOP_TARGET]].normalizedX;

		double realHeight = BASKET_TOP_ELEVATION - BASKET_MIDDLE_ELEVATION;
		if (targetCase[LEFT_TARGET] >= 0)
		{
			distance = GetDistanceFromHeight(realHeight, fabs(bestTargets[targetCase[LEFT_TARGET]].centerY - bestTargets[targetCase[TOP_TARGET]].centerY));
		}
		else if (targetCase[RIGHT_TARGET] >= 0)
		{
			distance = GetDistanceFromHeight(realHeight, fabs(bestTargets[targetCase[RIGHT_TARGET]].centerY - bestTargets[targetCase[TOP_TARGET]].centerY));
		}
	}
	else if (targetCase[BOTTOM_TARGET] >= 0 && (targetCase[LEFT_TARGET] >= 0 || targetCase[RIGHT_TARGET] >= 0))
	{
		//One of the bottom diagonals
		offset = bestTargets[targetCase[BOTTOM_TARGET]].normalizedX;

		double realHeight = BASKET_MIDDLE_ELEVATION - BASKET_BOTTOM_ELEVATION;
		if (targetCase[LEFT_TARGET] >= 0)
		{
			distance = GetDistanceFromHeight(realHeight, fabs(bestTargets[targetCase[BOTTOM_TARGET]].centerY - bestTargets[targetCase[LEFT_TARGET]].centerY));
		}
		else if (targetCase[RIGHT_TARGET] >= 0)
		{
			distance = GetDistanceFromHeight(realHeight, fabs(bestTargets[targetCase[BOTTOM_TARGET]].centerY - bestTargets[targetCase[RIGHT_TARGET]].centerY));
		}

	}
	else if( targetCase[LEFT_TARGET] >= 0 && targetCase[RIGHT_TARGET] >= 0 )
	{
		//Both side targets
		offset = (bestTargets[targetCase[RIGHT_TARGET]].normalizedX + bestTargets[targetCase[LEFT_TARGET]].normalizedX) / 2.0;
		distance = (bestTargets[targetCase[LEFT_TARGET]].distance + bestTargets[targetCase[RIGHT_TARGET]].distance) / 2.0;
	}

}
