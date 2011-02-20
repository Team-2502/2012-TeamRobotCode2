#ifndef VISION_H
#define VISION_H

#include "WPILib.h"

/*typedef enum Region {
	NorthWest, North,  NorthEast,
	West,      Center, East,
	SouthWest, South,  SouthEast
};

struct TargetReport
{
	Region region;
	double area;
};*/

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
