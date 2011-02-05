#ifndef ARMCLASS_H
#define ARMCLASS_H

#include <WPILib.h>
#include "VisionRoutines.h"
enum level
{
	sideFirst=29375,
	middleFirst=37275,
	loadingLevel=54600,
	sideSecond=64625,
	middleSecond=72625
};
enum shape
{
	triangle,
	square,
	circle
};

class Arm
{
public:
	Arm(int liftJagPort, int liftEncPort, int rightClawJag, int rightClawJag, int leftClawJag, int leftClawEnc);
	void snapToPeg();
	void setHeight(double height);
	void setHorizontal(double horizontal);
	void setWidth(double width);
	void setShape(int shape);
	void setLeftRod(double left);
	void setRightRod(double right);
	bool getClawState();
	double getHeight();
	double getHorizontal();
	double getWidth();
	double getShape();
private:
	Vision* camera;
	Encoder* liftEnc,rightClawEnc,leftClawEnc;
	Jaguar* liftJag,rightClawJag,leftClawJag;
};

#endif // ARM