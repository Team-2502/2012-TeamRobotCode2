#include <WPILib.h>
#include <algorithm>
#include <vector>
#include <cstdarg>
#include <cmath>
#include <fstream>
#include "SquareFinder.h"
#include "Math.h"
#include "DisplayWriter.h"
#include "Singleton.h"

static bool ParticleLogging = false;	// false to turn off; true to turn on

void SquareFinder::reservePrimaryLines() { primaryDisplay.Reserve(0); }
void SquareFinder::reserveSecondaryLines() { secondaryDisplay.Reserve(0); }


SquareFinder::SquareFinder()
{
	lumPlane = imaqCreateImage(IMAQ_IMAGE_U8, 7);
}

SquareFinder::~SquareFinder()
{
	imaqDispose(lumPlane);
}

void SquareFinder::GetBestTargets(HSLImage *img, vector<TargetReport> &targets, int &count)
{
	//	static double MagicConstantX = 320.0/tan(degToRad(23.5)); //X_Res/tan(fov_x/2)
	static double MagicConstantY = (2*240.0/2.0)/tan(degToRad(20.44)); //(2*Y_Res/Height_ft)/tan(fov_y/2)
	if(!img) 
	{
		count = 0;
		return;
	}

	int height = img->GetHeight();
	int width = img->GetWidth();
	Image *image = img->GetImaqImage();

	//Parameter, Lower, Upper, Calibrated?, Exclude?
	ParticleFilterCriteria2 particleCriteria_initial[1] = { {IMAQ_MT_AREA_BY_IMAGE_AREA,25,100,0,1} };
	ParticleFilterCriteria2 particleCriteria[1] = { {IMAQ_MT_RATIO_OF_EQUIVALENT_RECT_SIDES,1,2,0,0} };
	ParticleFilterOptions particleFilterOptions[1] = { {FALSE,0,FALSE} };
	ParticleFilterOptions particleFilterOptions_conn8[1] = { {FALSE,0,TRUE} };
	int numParticles;

	imaqExtractColorPlanes(image, IMAQ_HSL, NULL, NULL, lumPlane);

	image = lumPlane;

	imaqAutoThreshold2(image, image, 2, IMAQ_THRESH_INTERCLASS, NULL);
	imaqParticleFilter3(image, image, particleCriteria_initial, 1, particleFilterOptions, NULL, &numParticles);
	imaqFillHoles(image, image, TRUE);

	int pKernel[9] = {1,1,1,1,1,1,1,1,1};
	StructuringElement structElem[1] = { { 3, 3, FALSE, pKernel } };
	imaqSizeFilter(image, image, TRUE, 2, IMAQ_KEEP_LARGE, structElem);

	imaqParticleFilter3(image, image, particleCriteria, 1, particleFilterOptions_conn8, NULL, &numParticles);

	vector<TargetReport> reports;
	
	ofstream STREAM;
	
	if (ParticleLogging) {
		STREAM.open("/ni-rt/system/logs/outputShooter.txt", ios::out | ios::app);
		STREAM << numParticles << "\n";
	}
	

	//Use the most proportional.
	if(imaqCountParticles(image,TRUE,&numParticles)) {
		TargetReport report;
		if(numParticles >= 1) {
			for(int i = 0; i < numParticles; i++) {
				double h,w,area,x,y;
				imaqMeasureParticle(image,i,FALSE,IMAQ_MT_BOUNDING_RECT_HEIGHT,&h);
				imaqMeasureParticle(image,i,FALSE,IMAQ_MT_BOUNDING_RECT_WIDTH,&w);
				imaqMeasureParticle(image,i,FALSE,IMAQ_MT_AREA,&area);
				imaqMeasureParticle(image,i,FALSE,IMAQ_MT_BOUNDING_RECT_LEFT,&x);
				imaqMeasureParticle(image,i,FALSE,IMAQ_MT_BOUNDING_RECT_TOP,&y);
				
				if (ParticleLogging) {
					STREAM << x << ", " << y << ", " << w << ", " << h << "\n";
				}
				
				if(area/(w*h) > 0.8 && (w*h) > 125 && w > h) {
					report.height = h;
					report.width  = w;
					
					report.size = area;
					imaqMeasureParticle(image,i,FALSE,IMAQ_MT_CENTER_OF_MASS_X,&report.normalizedX);
					imaqMeasureParticle(image,i,FALSE,IMAQ_MT_CENTER_OF_MASS_Y,&report.normalizedY);
					imaqMeasureParticle(image,i,FALSE,IMAQ_MT_BOUNDING_RECT_LEFT,&report.x);
					imaqMeasureParticle(image,i,FALSE,IMAQ_MT_BOUNDING_RECT_TOP,&report.y);
					report.centerX = report.normalizedX;
					report.centerY = report.normalizedY;
					report.normalizedX = (-1.0+2.0*((report.normalizedX)/width)); //Map to [-1.0,1.0]
					report.normalizedY = (-1.0+2.0*((report.normalizedY)/height));
					report.normalizedWidth = (w / width);
					report.normalizedHeight = (h / height);
					report.distance = MagicConstantY / h; //In feet.
					reports.push_back(report);
				}
			}
		}
	}

	
	if (ParticleLogging) {
		STREAM.close();
	}
	
	sort(reports.begin(),reports.end());
	if (reports.size() > 4)
	{
		reports.resize(4, TargetReport());
	}
	targets = reports;
	count = reports.size();

	/*
	if(reports.size()) {
		for(unsigned i = 0; i < reports.size() && i < 4; i++) {
			TargetReport tr = reports[i];
			Image* squareImage = img->GetImaqImage();
			Rect r;
			r.height = (int)tr.height;
			r.width = (int)tr.width;
			r.top = (int)tr.y;
			r.left = (int)tr.x;
			Rect rX;
			rX.height = 1;
			rX.width = 5;
			rX.top = int((tr.normalizedY+1.0)/2*240);
			rX.left = int((tr.normalizedX+1.0)/2*320);
			Rect rY;
			rX.height = 5;
			rX.width = 1;
			rX.top = int((tr.normalizedY+1.0)/2*240);
			rX.left = int((tr.normalizedX+1.0)/2*320);
			float colors[] = {(float)0x00FF00, (float)0xFF0000, (float)0x0000FF, (float)0xFF00FF, 0.0,0.0,0.0,0.0,0.0};
			imaqDrawShapeOnImage(squareImage,squareImage,r,IMAQ_DRAW_VALUE,IMAQ_SHAPE_RECT,colors[i]);
			imaqDrawShapeOnImage(squareImage,squareImage,rY,IMAQ_DRAW_VALUE,IMAQ_SHAPE_RECT,colors[i]);
			imaqDrawShapeOnImage(squareImage,squareImage,rX,IMAQ_DRAW_VALUE,IMAQ_SHAPE_RECT,colors[i]);
			imaqWriteJPEGFile(squareImage,"/frame.jpg",750,0);
		}
	}
	*/
}

