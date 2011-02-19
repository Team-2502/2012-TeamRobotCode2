#ifndef PIDCAMERACLASS_H
#define PIDCAMERA_H

#include "WPILib.h"
#include "VisionRoutines.h"
#include "config.h"

typedef enum Axis {
	leftShift,
	verticalAxis,
	rightShift
};

class PIDCamera : public PIDSource
{
public:
	PIDCamera(Vision* cam, Axis dimension);
	double PIDGet();
private:
	Vision* camera;
	Axis axis;
};

#endif // PIDCAMERA
