#include "PIDCamera.h"

PIDCamera::PIDCamera(Vision* cam, Axis dimension)
{
	camera=cam;
	axis=dimension;
	width=circle;
}
double PIDCamera::PIDGet()
{
	TargetReport target=camera->getNearestPeg();
	switch (axis)
	{
	case leftShift:
		return target.x-width/200.;
	case rightShift:
		return target.x+width/200.;
	default:
		return (2*target.y-YRESOLUTION)/YRESOLUTION;
	}
}
void PIDCamera::SetShape(Shape shape)
{
	width=shape;
}
