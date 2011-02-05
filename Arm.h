#ifndef ARMCLASS_H
#define ARMCLASS_H

#include <WPILib.h>
#include "VisionRoutines.h"

typedef enum Level {
	sideFirst=29375,
	middleFirst=37275,
	loadingLevel=54600,
	sideSecond=64625,
	middleSecond=72625
};
typedef enum Shape {
	triangle,
	square,
	circle
};

class Arm
{
public:
	Arm();
	void snapToPeg();
	void setHeight(double height);
	void setHorizontal(float horizontal);
	void setWidth(float width);
	void setShape(int shape);
	void setLeftRod(float left);
	void setRightRod(float right);
	bool getClawState();
	float getHeight();
	float getHorizontal();
	float getWidth();
	float getShape();
private:
	Vision* camera;
	Encoder* liftEnc,rightClawEnc,leftClawEnc;
	Jaguar* liftJag,rightClawJag,leftClawJag;
};

#endif // ARM