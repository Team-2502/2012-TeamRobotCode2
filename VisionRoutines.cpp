#include "Vision.h"
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
	camera = AxisCamera::GetInstance();
	camera.WriteResolution(kResolution_160x120);
	camera.WriteBrightness(0);
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
	camera.GetImage(constantImage);
	particleImage = constantImage->ThresholdHSL(0,255,0,255,244,255);
	ParticleAnalysisReport_struct report = particleImage->GetParticleAnalysisReport(3);
	
	delete particleImage;
	particleImage = 0;
	return ret;
}
