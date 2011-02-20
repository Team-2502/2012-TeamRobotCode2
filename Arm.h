#ifndef ARMCLASS_H
#define ARMCLASS_H

#include "WPILib.h"
#include "VisionRoutines.h"
#include "PIDCamera.h"

typedef enum Level {
	sideFirst=29375,
	middleFirst=37275,
	loadingLevel=54600,
	sideSecond=64625,
	middleSecond=72625
};

struct ErrorReport
{
	double vertical;
	double horizontal;
	double distance;
};

class Arm;

class Arm
{
public:
	~Arm();
	ErrorReport snapToPeg();
	void grab();
	void ungrab();
	void toggle();
	void setHeight(int armHeight);
	void setCenter(int center);
	void setWidth(int width);
	void setShape(Shape shape);
	void setLeftRod(int left);
	void setRightRod(int right);
	bool getClawState();
	int getHeight();
	int getCenter();
	int getWidth();
	int getShape();
	int getLeftRod();
	int getRightRod();
	static Arm* GetInstance() {return instance;}
private:
	Arm();
	Arm(int initHeight, int initWidth);
	Arm(int initHeight, int initLeft, int initRight);
	
	static Arm* instance;
	Vision* camera;
	Encoder* liftEnc;
	Encoder* rightClawEnc;
	Encoder* leftClawEnc;
	Jaguar* liftJag;
	Jaguar* rightClawJag;
	Jaguar* leftClawJag;
	PIDController* liftEncoderPID;
	PIDController* rightClawEncoderPID;
	PIDController* leftClawEncoderPID;
	PIDController* liftCameraPID;
	PIDController* rightClawCameraPID;
	PIDController* leftClawCameraPID;
	PIDCamera* leftPIDVisionSource;
	PIDCamera* liftPIDVisionSource;
	PIDCamera* rightPIDVisionSource;
	Shape shape;
	int leftClawPos, rightClawPos, height, rightOffset, leftOffset, heightOffset;
	void updatePID();
};

#endif // ARM

