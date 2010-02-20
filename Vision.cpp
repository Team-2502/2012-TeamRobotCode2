#include <algorithm>
#include <math.h>
#include "Vision.h"
#include "WPILib.h"
#include "Vision/PCVideoServer.h"
#include "nivision.h"
#include "Vision/MonoImage.h"

// These parameters set ellipse finding in the NI imaq (Image Aquisition) library.
// Refer to the CVI Function Reference PDF document installed with LabVIEW for
// additional information.
static EllipseDescriptor ellipseDescriptor = {
		3, 		// minMajorRadius
		200, 	// maxMajorRadius
		3, 		// minMinorRadius
		100		// maxMinorRadius
};

static CurveOptions curveOptions = {	IMAQ_NORMAL_IMAGE,	// extractionMode
		40, 				// threshold
		IMAQ_NORMAL, 		// filterSize
		25, 				// minLength
		15, 				// rowStepSize 
		15, 				// columnStepSize
		10, 				// maxEndPointGap
		1,					// onlyClosed
		0					// subpixelAccuracy
};

static ShapeDetectionOptions shapeOptions = {
		IMAQ_GEOMETRIC_MATCH_SHIFT_INVARIANT,	// mode
		NULL,			// angle ranges
		0,				// num angle ranges
		{75, 125},		// scale range
		500				// minMatchScore
};


double Target::getHorizontalAngle()
{
	double x = xPos;
	x = x * 9.0 / xMax;
	x = atan2(x, 20.0);
	x = x * 180.0 / 3.14159;
	return x;
}

//Utility function for sort()
int compareTargets(Target t1, Target t2)
{
	if (t1.score > t2.score) return 1;
	if (t1.score < t2.score) return -1;
	return 0;
}

vector<Target> Target::findCircularTargets(HSLImage *image)
{
	wpi_assert(image != NULL);
	int width = image->GetWidth();
	int height = image->GetHeight();

	vector<Target> sortedTargets;

	// get the luminance plane only for the image to make the code
	// insensitive to lighting conditions.
	MonoImage  *luminancePlane = image->GetLuminancePlane();
	vector<EllipseMatch> *results = luminancePlane->DetectEllipses(&ellipseDescriptor, 
			&curveOptions,
			&shapeOptions,
			NULL);
	delete luminancePlane;

	if (!results->size())
		return sortedTargets;

	// create a list of targets corresponding to each ellipse found
	// in the image.
	for (unsigned int i = 0; i < results->size(); i++)
	{
		Target target;
		EllipseMatch e = results->at(i);
		target.rawScore = e.score;
		target.score = (e.majorRadius * e.minorRadius) / (1001 - e.score) / (height * width) * 100;
		target.majorRadius = e.majorRadius / height;
		target.minorRadius = e.minorRadius / height;
		//always divide by height so that x and y are same units
		target.xPos = (2.0 * e.position.x - width) / height;
		target.yPos = (2.0 * e.position.y - height) / height;
		target.rotation = e.rotation;
		target.xMax = (double)width / height;
		target.bothFound = false;
		sortedTargets.push_back(target);
	}
	delete results;

	// sort the list of targets by score
	sort(sortedTargets.begin(), sortedTargets.end(), compareTargets);

	// go through each target found in descending score order and look
	// for another target whose center is contained inside of this target
	// Those concentric targets get a score which is the sum of both targets
	vector<Target> combinedTargets;
	while (sortedTargets.size() > 0)
	{
		vector<Target>::iterator iter = sortedTargets.begin();
		Target t1 = *iter++;
		for (; iter < sortedTargets.end(); iter++)
		{
			Target t2 = *iter;

			// check if the two are concentric
			if ((fabs(t1.xPos - t2.xPos) < min(t1.minorRadius, t2.minorRadius)) &&
					(fabs(t1.yPos - t2.yPos) < min(t1.majorRadius, t2.majorRadius)))
			{
				// create the information for the combined target
				// (the 2 concentric ellipses)
				t1.xPos = (t1.xPos + t2.xPos) / 2;
				t1.yPos = (t1.yPos + t2.yPos) / 2;
				t1.rawScore += t2.rawScore;
				t1.score = (t1.score + t2.score) * 2.0;  // add a 2x bonus for concentric
				t1.majorRadius = max(t1.majorRadius, t2.majorRadius);
				t1.minorRadius = max(t1.minorRadius, t2.minorRadius);
				t1.bothFound = true;
				sortedTargets.erase(iter);
				break;
			}
		}
		sortedTargets.erase(sortedTargets.begin());
		combinedTargets.push_back(t1);
	}

	// sort the combined targets so the highest scoring one is first
	sort(combinedTargets.begin(), combinedTargets.end(), compareTargets);

	return combinedTargets;
}

Joystick* Vision::driveStick = 0;
int Vision::button = 0;

Vision::Vision(int alignButton, Joystick *ds)
{
	button = alignButton;
	driveStick = ds;
	visionTask = new Task("2502Vn", (FUNCPTR) loop);
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
	AxisCamera &camera = AxisCamera::GetInstance();
	camera.WriteResolution(AxisCamera::kResolution_320x240);
	Wait(3.0);
	HSLImage image;
	
	while(true)
	{
		camera.GetImage(&image);
		Target bestTarget = Target::findCircularTargets(&image).front();
		if(driveStick->GetRawButton(button))
		{
			if(bestTarget.xPos > 192) {
				//Rotate counter-clockwise
			} else if(bestTarget.xPos < 128) {
				//Rotate clockwise.
			}
		}
		Wait(0.1);
	}
}
