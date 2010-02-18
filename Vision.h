#ifndef VISION_H
#define VISION_H
#include "WPILib.h"
#include "Vision/PCVideoServer.h"

//class Target
//{
//public:
//    double majorRadius;
//    double minorRadius;
//    double rawScore;
//    double xPos;
//    double yPos;
//    double score;
//    double rotation;
//    double xMax;
//    bool bothFound;
//
//    double getHorizontalAngle();
//    static vector<Target> findCircularTargets(HSLImage *image);
//};

class Vision
{
public:
	Vision(int alignButton = 0, Joystick *ds = 0);
	void start();
	void stop();
	void startServer();
	void stopServer();
	
private:
	static void loop();
	static int button;
	static Joystick *driveStick;
	
	PCVideoServer* video;
	Task* visionTask;
};

#endif
