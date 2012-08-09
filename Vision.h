#ifndef VISION_H
#define VISION_H

#include "WPILib.h"
#include "DisplayWriter.h"
#include <vector>

struct TargetReport 
{
	double width;
	double height;
	double x;
	double y;
	double centerX;
	double centerY;
	double size;
	double normalizedX; //units of Joystick plane [-1, 1]
	double normalizedY; //units of Joystick plane [-1, 1]
	double normalizedWidth;
	double normalizedHeight;
	double distance; //fts
	bool operator<(TargetReport &rhs) {return normalizedY > rhs.normalizedY;}
};

struct TargetPair
{
	int a;
	int b;
	bool set;
};


class VisionSpecifics
{
public:
	virtual ~VisionSpecifics() {}
	virtual void GetBestTargets(HSLImage *img, vector<TargetReport> &targets, int &count) = 0;
};

class Vision
{
public:
	Vision(VisionSpecifics *backend);
	~Vision();
	
	void start();
	void stop();
	
    /**
     * Find the best target.
     *
     * \param offset the relative offset to the left or right of the camera.
     * \param distance the distance to the target.
     * \param targetLevel the height level of the target.
     */
	void FindTarget(double& offset, double& distance);
    
	TargetReport GetBestTarget() const { return bestTargets[0]; }

	void reservePrimaryLines();
	void reserveSecondaryLines();
	
	void setEnabled(bool e) { enabled = e; }

	DisplayWriter primaryDisplay;
	DisplayWriter secondaryDisplay;
    
private:
	static void loop();
    void GetTargetCase(vector <TargetReport> &targets, int numtargets, int & top, int & left, int & right, int & bottom);
    bool isHorizontallyAligned(TargetReport &targets1, TargetReport &targets2);
    bool isVerticallyAligned(TargetReport &targets1, TargetReport &targets2);
    bool isBottomTarget( TargetReport &target );
	Task* visionTask;
	
	static bool enabled;
    static int bestTargetCount;
	static vector<TargetReport> bestTargets;
	static AxisCamera* cam;
	static VisionSpecifics* engine;
};

#endif

