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

class Arm
{
public:
	Arm(float armHeight, float clawWidth);
	~Arm();
	ErrorReport snapToPeg();
	void grab();
	void ungrab();
	void toggle();
	void setHeight(float armHeight);
	void setCenter(float center);
	void setWidth(float width);
	void setShape(Shape shape);
	void setLeftRod(float left);
	void setRightRod(float right);
	bool getClawState();
	float getHeight();
	float getCenter();
	float getWidth();
	float getShape();
	float getLeftRod();
	float getRightRod();
private:
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
	float leftClawPos, rightClawPos, height;
	void updatePID();
};

#endif // ARM
