#include "Arm.h"
#include "config.h"

Arm::Arm()
{
	Arm(0,circle);
}

Arm::Arm(int initHeight, int initWidth)
{
	Arm(initHeight, -initWidth/2, initWidth/2);
}

Arm::Arm(int initHeight, int initLeft, int initRight)
{
	camera = Vision::GetInstance();

	liftEnc = new Encoder(ARM_CHAIN_ENCODER_A_CHANNEL, ARM_CHAIN_ENCODER_B_CHANNEL);
	rightClawEnc = new Encoder(RIGHT_CLAW_ENCODER_A_CHANNEL, RIGHT_CLAW_ENCODER_B_CHANNEL);
	leftClawEnc = new Encoder(LEFT_CLAW_ENCODER_A_CHANNEL, LEFT_CLAW_ENCODER_B_CHANNEL);
	
	liftJag = new Jaguar(WINCH_CHANNEL);
	rightClawJag = new Jaguar(RIGHT_CLAW_CHANNEL);
	leftClawJag = new Jaguar(LEFT_CLAW_CHANNEL);
	
	liftJag->SetSafetyEnabled(false);
	rightClawJag->SetSafetyEnabled(false);
	leftClawJag->SetSafetyEnabled(false);
	
	liftEncoderPID = new PIDController(PID_P/10.,PID_I/10.,PID_D/10.,liftEnc,liftJag);
	rightClawEncoderPID = new PIDController(PID_P/10.,PID_I/10.,PID_D/10.,rightClawEnc,rightClawJag);
	leftClawEncoderPID = new PIDController(PID_P/10.,PID_I/10.,PID_D/10.,leftClawEnc,leftClawJag);
	
	setShape(circle);
	
	rightOffset = initHeight;
	leftOffset = initRight;
	heightOffset = initLeft;
	updatePID();
}

Arm::~Arm()
{
	delete liftEncoderPID;
	delete rightClawEncoderPID;
	delete leftClawEncoderPID;
	delete liftEnc;
	delete rightClawEnc;
	delete leftClawEnc;
	delete liftJag;
	delete rightClawJag;
	delete leftClawJag;
}

ErrorReport Arm::getError()
{
	ErrorReport error;
	error.vertical=liftEncoderPID->GetError();
	error.horizontal=(rightClawEncoderPID->GetError()+leftClawEncoderPID->GetError())/2;
	error.distance=rightClawEncoderPID->GetError()-leftClawEncoderPID->GetError();
	return error;
}

void Arm::snapToPeg()
{
	TargetReport target=camera->getNearestPeg();
	setHeight(getHeight()+(int)target.y/YRESOLUTION*(int)target.area/XRESOLUTION/YRESOLUTION*VERTICAL_SNAP_MULTIPLIER);
	setCenter((int)target.x/XRESOLUTION*(int)target.area/XRESOLUTION/YRESOLUTION*HORIZONTAL_SNAP_MULTIPLIER);
}

void Arm::grab()
{
	setHeight(shape);
}

void Arm::ungrab()
{
	setHeight(0);
}

void Arm::toggle()
{
	if (getClawState())
		ungrab();
	else
		grab();
}

void Arm::updatePID()
{
	liftEncoderPID->SetSetpoint(getHeight()-heightOffset);
	rightClawEncoderPID->SetSetpoint(getLeftRod()-rightOffset);
	leftClawEncoderPID->SetSetpoint(getRightRod()-leftOffset);
}

void Arm::setHeight(int armHeight)
{
	if (armHeight>MAX_LIFT_HEIGHT) armHeight=MAX_LIFT_HEIGHT;
	else if (armHeight<0) armHeight=0;
	height=armHeight;
	updatePID();
}

void Arm::setCenter(int center)
{
	int width=getWidth();
	setLeftRod(center-width/2);
	setRightRod(center+width/2);
	updatePID();
}

void Arm::setWidth(int width)
{
	int center=getCenter();
	setLeftRod(center-width/2);
	setRightRod(center+width/2);
	updatePID();
}

void Arm::setShape(Shape newShape)
{
	shape=newShape;
}

void Arm::setLeftRod(int left)
{
	if (left<-MAX_WIDTH/2) left=-MAX_WIDTH/2;
	if (left>MAX_WIDTH/2) left=MAX_WIDTH/2;
	leftClawPos=left;
	updatePID();
}

void Arm::setRightRod(int right)
{
	if (right<-MAX_WIDTH/2) right=-MAX_WIDTH/2;
	if (right>MAX_WIDTH/2) right=MAX_WIDTH/2;
	rightClawPos=right;
	updatePID();
}

bool Arm::getClawState()
{
	return getWidth()>500;
}

int Arm::getHeight()
{
	return height;
}

int Arm::getCenter()
{
	return rightClawPos+getWidth()/2;
}

int Arm::getWidth()
{
	return rightClawPos-leftClawPos;
}

int Arm::getShape()
{
	return shape;
}

int Arm::getLeftRod()
{
	return leftClawPos;
}

int Arm::getRightRod()
{
	return rightClawPos;

}
