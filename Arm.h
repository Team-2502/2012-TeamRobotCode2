#ifndef ARMCLASS_H
#define ARMCLASS_H

#include "WPILib.h"
#include "VisionRoutines.h"

typedef enum Level {
	sideFirst=29375,
	middleFirst=37275,
	loadingLevel=54600,
	sideSecond=64625,
	middleSecond=72625
};

typedef enum Shape {
	triangle=950,
	square=1000,
	circle=1250
};

class Arm
{
public:
	Arm(float armHeight, float clawWidth);
	void snapToPeg();
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
private:
	Vision* camera;
	Encoder* liftEnc;
	Encoder* rightClawEnc;
	Encoder* leftClawEnc;
	Jaguar* liftJag;
	Jaguar* rightClawJag;
	Jaguar* leftClawJag;
	Shape shape;
	float leftClawPos, rightClawPos, height;
	void updatePID();
};

#endif // ARM
