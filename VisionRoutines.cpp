#include "VisionRoutines.h"
#include "nivision.h"
#include <cmath>

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
	if(particleImage)
		delete constantImage;
	if(particleImage)
		delete particleImage;
}

TargetReport Vision::getNearestPeg()
{
	TargetReport ret;
	ret.x = 0;
	ret.y = 0;
	ret.area = 0;
	camera->GetImage(constantImage);
	particleImage = constantImage->ThresholdHSL(0,255,0,255,225,255);
	vector<ParticleAnalysisReport_struct> *report = particleImage->GetOrderedParticleAnalysisReports();
	if(report->size() == 0)
		return ret;
	ParticleAnalysisReport_struct largest = report->front();
	ret.x = largest.center_mass_x;
	ret.y = largest.center_mass_y;
	ret.area = largest.particleArea;
	delete particleImage;
	particleImage = 0;
	return ret;
}
