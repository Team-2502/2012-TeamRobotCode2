#include "PIDCamera.h"

PIDCamera::PIDCamera(Vision* cam, Axis dimension)
{
	camera=cam;
	axis=dimension;
}
double PIDCamera::PIDGet()
{
	TargetReport target=camera->getNearestPeg();
	switch (axis)
	{
	case leftShift:
		return target.x-CLAW_SPACE/2;
	case rightShift:
		return target.x+CLAW_SPACE/2;
	default:
		return (2*target.y-YRESOLUTION)/YRESOLUTION;
	}
}
