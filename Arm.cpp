/*#include "Arm.h"
#include "config.h"
Arm::Arm()
{
	Arm(0,circle);
}
Arm::Arm(int armHeight, int clawWidth)
{
	camera = Vision::GetInstance();
	leftPIDVisionSource = new PIDCamera(camera, leftShift);
	liftPIDVisionSource = new PIDCamera(camera, verticalAxis);
	rightPIDVisionSource = new PIDCamera(camera, rightShift);
	
	liftCameraPID = new PIDController(PID_P/10.,PID_I/10.,PID_D/10.,liftPIDVisionSource,liftJag);
	rightClawCameraPID = new PIDController(PID_P/10.,PID_I/10.,PID_D/10.,rightPIDVisionSource,rightClawJag);
	leftClawCameraPID = new PIDController(PID_P/10.,PID_I/10.,PID_D/10.,leftPIDVisionSource,leftClawJag);
	
	liftCameraPID->Disable();
	rightClawCameraPID->Disable();
	leftClawCameraPID->Disable();
	
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
	
	liftEncoderPID->Enable();
	rightClawEncoderPID->Enable();
	leftClawEncoderPID->Enable();
	
	setShape(circle);
	setHeight(armHeight);
	setRightRod(-circle/2);
	setLeftRod(circle/2);
}

Arm::~Arm()
{
	delete liftEncoderPID;
	delete rightClawEncoderPID;
	delete leftClawEncoderPID;
	delete liftCameraPID;
	delete rightClawCameraPID;
	delete leftClawCameraPID;
	delete leftPIDVisionSource;
	delete liftPIDVisionSource;
	delete rightPIDVisionSource;
	delete liftEnc;
	delete rightClawEnc;
	delete leftClawEnc;
	delete liftJag;
	delete rightClawJag;
	delete leftClawJag;
}

ErrorReport Arm::snapToPeg()
{
	ErrorReport error;
	liftEncoderPID->Disable();
	rightClawEncoderPID->Disable();
	leftClawEncoderPID->Disable();
	liftCameraPID->Enable();
	rightClawCameraPID->Enable();
	leftClawCameraPID->Enable();
	error.vertical=liftCameraPID->GetError();
	error.horizontal=(rightClawCameraPID->GetError()+leftClawCameraPID->GetError())/2;
	error.distance=rightClawCameraPID->GetError()-leftClawCameraPID->GetError();
	return error;
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
	liftEncoderPID->SetSetpoint(getHeight());
	rightClawEncoderPID->SetSetpoint(getLeftRod());
	leftClawEncoderPID->SetSetpoint(getRightRod());
	liftCameraPID->Disable();
	rightClawCameraPID->Disable();
	leftClawCameraPID->Disable();
	liftEncoderPID->Enable();
	rightClawEncoderPID->Enable();
	leftClawEncoderPID->Enable();
}
void Arm::setHeight(int armHeight)
{
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
	leftPIDVisionSource->SetShape(shape);
	rightPIDVisionSource->SetShape(shape);
}
void Arm::setLeftRod(int left)
{
	leftClawPos=left;
	updatePID();
}
void Arm::setRightRod(int right)
{
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
*/
