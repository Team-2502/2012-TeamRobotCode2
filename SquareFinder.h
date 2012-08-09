#ifndef SQUAREFINDER_H
#define SQUAREFINDER_H

#include "vision.h"

class SquareFinder : public VisionSpecifics
{
public:
	SquareFinder();
	~SquareFinder();
	
	void GetBestTargets(HSLImage *img, vector<TargetReport> &targets, int &count);
	
	void reservePrimaryLines();
	void reserveSecondaryLines();
	
private:
	DisplayWriter primaryDisplay;
	DisplayWriter secondaryDisplay;

	Image* lumPlane;
};

#endif
