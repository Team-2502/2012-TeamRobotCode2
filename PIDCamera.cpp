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
	case horizontalAxis:
		return (2*target.x-XRESOLUTION)/XRESOLUTION;
	case verticalAxis:
		return (2*target.y-YRESOLUTION)/YRESOLUTION;
	default:
		return 1/(target.area-100);
	}
}
