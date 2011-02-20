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
}

TargetReport Vision::getNearestPeg()
{
	TargetReport ret;
	camera->GetImage(constantImage);
	particleImage = constantImage->ThresholdHSL(0,255,0,255,225,255);
	Image* img = particleImage->GetImaqImage();
	ParticleFilterCriteria2 *filterCriteria = new ParticleFilterCriteria2;
	filterCriteria->parameter = IMAQ_MT_AREA;
	filterCriteria->lower = 850.00;
	filterCriteria->upper = 9001.0; //It's over 9000!!!!1!one!
	filterCriteria->calibrated = 0;
	filterCriteria->exclude = 1;
	imaqParticleFilter2(img,img,filterCriteria,1,false,false,0);
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
