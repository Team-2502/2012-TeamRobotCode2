#include "Arm.h"
#include "config.h"

Arm::Arm(float armHeight, float clawWidth)
{
	camera = Vision::GetInstance();
	
	liftEnc = new Encoder(ARM_CHAIN_ENCODER_A_CHANNEL, ARM_CHAIN_ENCODER_B_CHANNEL);
	rightClawEnc = new Encoder(RIGHT_CLAW_ENCODER_A_CHANNEL, RIGHT_CLAW_ENCODER_B_CHANNEL);
	leftClawEnc = new Encoder(LEFT_CLAW_ENCODER_A_CHANNEL, LEFT_CLAW_ENCODER_B_CHANNEL);
	
	liftJag = new Jaguar(WINCH_CHANNEL);
	rightClawJag = new Jaguar(RIGHT_CLAW_CHANNEL);
	leftClawJag = new Jaguar(LEFT_CLAW_CHANNEL);
	
	liftPID = new PIDController(PID_P/10.,PID_I/10.,PID_D/10.,liftEnc,liftJag);
	rightClawPID = new PIDController(PID_P/10.,PID_I/10.,PID_D/10.,rightClawEnc,rightClawJag);
	leftClawPID = new PIDController(PID_P/10.,PID_I/10.,PID_D/10.,leftClawEnc,leftClawJag);
	
	setShape(circle);
	setHeight(armHeight);
	setRightRod(-circle/100./2);
	setLeftRod(circle/100./2);
}
Arm::~Arm()
{
	delete camera;
	delete liftPID;
	delete rightClawPID;
	delete leftClawPID;
	delete liftEnc;
	delete rightClawEnc;
	delete leftClawEnc;
	delete liftJag;
	delete rightClawJag;
	delete leftClawJag;
}
void Arm::snapToPeg()
{
	//implement
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
	liftPID->SetSetpoint(getHeight());
	rightClawPID->SetSetpoint(getLeftRod());
	leftClawPID->SetSetpoint(getRightRod());
}
void Arm::setHeight(float armHeight)
{
	height=armHeight;
	updatePID();
}
void Arm::setCenter(float center)
{
	float width=getWidth();
	setLeftRod(center-width/2);
	setRightRod(center+width/2);
	updatePID();
}
void Arm::setWidth(float width)
{
	float center=getCenter();
	setLeftRod(center-width/2);
	setRightRod(center+width/2);
	updatePID();
}
void Arm::setShape(Shape newShape)
{
	shape=newShape;
}
void Arm::setLeftRod(float left)
{
	leftClawPos=left;
	updatePID();
}
void Arm::setRightRod(float right)
{
	rightClawPos=right;
	updatePID();
}
bool Arm::getClawState()
{
	return getWidth()>500;
}
float Arm::getHeight()
{
	return height;
}
float Arm::getCenter()
{
	return rightClawPos+getWidth()/2;
}
float Arm::getWidth()
{
	return rightClawPos-leftClawPos;
}
float Arm::getShape()
{
	return shape;
}
float Arm::getLeftRod()
{
	return leftClawPos;
}
float Arm::getRightRod()
{
	return rightClawPos;

}
