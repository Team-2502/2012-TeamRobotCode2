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

typedef enum Shape {
	triangle=950,
	square=1000,
	circle=1250
};

class PIDCamera : public PIDSource
{
public:
	PIDCamera(Vision* cam, Axis dimension);
	double PIDGet();
	void SetShape(Shape shape);
private:
	Vision* camera;
	Axis axis;
	Shape width;
};

#endif // PIDCAMERA
