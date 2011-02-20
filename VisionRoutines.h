#ifndef VISION_H
#define VISION_H

#include "WPILib.h"

struct TargetReport
{
	float x;
	float y;
	float area;
};

class Vision
{
	public:
		static Vision* GetInstance();
		TargetReport getNearestPeg();
		~Vision();

		
	private:
		Vision();
		static Vision* visionInstance;
		HSLImage *constantImage;
		BinaryImage *particleImage;
		AxisCamera *camera;
};

#endif
