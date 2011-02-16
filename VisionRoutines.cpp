#include "VisionRoutines.h"
#include "Vision2009/VisionAPI.h"

Vision* Vision::visionInstance = NULL;

Vision* Vision::GetInstance()
{
	if(!visionInstance)
		visionInstance = new Vision;
	return visionInstance;
}

Vision::Vision()
{
	camera = &AxisCamera::GetInstance();
	camera->WriteResolution(AxisCameraParams::kResolution_160x120);
	camera->WriteBrightness(0);
	constantImage = new HSLImage;
}

Vision::~Vision()
{
	delete constantImage;
	if(particleImage)
		delete particleImage;
	visionInstance = NULL;
}

TargetReport Vision::getNearestPeg()
{
	TargetReport ret;
	camera->GetImage(constantImage);
	particleImage = constantImage->ThresholdHSL(0,255,0,255,244,255);
	vector<ParticleAnalysisReport_struct> *report = particleImage->GetOrderedParticleAnalysisReports();
	if(report->size() == 0)
		return ret;
	ParticleAnalysisReport_struct largest = report->front();
	if(largest.center_mass_y > 80) { //North
		if(largest.center_mass_x > 106) {
			ret.region = NorthEast;
		} else if(largest.center_mass_x > 53) {
			ret.region = North;
		} else {
			ret.region = NorthWest;
		}
	} else if(largest.center_mass_y > 40) { //Center
		if(largest.center_mass_x > 106) {
			ret.region = West;
		} else if(largest.center_mass_x > 53) {
			ret.region = Center;
		} else {
			ret.region = East;
		}
	} else { //South
		if(largest.center_mass_x > 106) {
			ret.region = SouthWest;
		} else if(largest.center_mass_x > 53) {
			ret.region = South;
		} else {
			ret.region = SouthEast;
		}
	}
	ret.area = largest.particleArea;
	delete particleImage;
	particleImage = 0;
	return ret;
}
