#include "MyRobot.h"

BetaRobot::BetaRobot(void)
{
	joystick = new JoystickWrapper(1, Extreme3DPro);
	joystick->SetSnapPoints(8);
	drive = new DriverWrapper(Mecanum);
	lift = new Encoder(ARM_CHAIN_ENCODER_A_CHANNEL, ARM_CHAIN_ENCODER_B_CHANNEL);
	servo = new Servo(DIGITAL_SIDECAR_PORT,SERVO_CHANNEL_START);
	servo->SetSafetyEnabled(false);
	mini = new Minibot();
	#ifdef USE_GYRO
	gyro = new Gyro(GYRO_SLOT,GYRO_CHANNEL);
	#endif
	arm = new Arm();
	pcvs = new PCVideoServer;
	myState = PlaceTube;
	eye = Vision::GetInstance();
	time = new Timer();
	shapeLockStart=-9001;
	triggerLockStart=-9001;
	POVStart=-9001;
	miniStart=0;
	triggerRelease=false;
	shapeRelease=false;
}

void BetaRobot::AutonomousPeriodic(void)
{
	switch(myState)
	{
	case TrackLine:
		DisplayWrapper::GetInstance()->PrintfLine(4,"Auto: Implement LT.");
		DisplayWrapper::GetInstance()->Output();
		break;
	case PlaceTube:
		TargetReport report=eye->getNearestPeg();
		if(report.y > (int)(2.0*YRESOLUTION/3.0)) { //top third
			arm->setHeight(sideSecond);
			DisplayWrapper::GetInstance()->PrintfLine(4,"Auto: Arm up.");
			DisplayWrapper::GetInstance()->Output();
		} else if(report.y < (int)(YRESOLUTION/3.0)) { //bottom third
			arm->setHeight(sideFirst);
			DisplayWrapper::GetInstance()->PrintfLine(4,"Auto: Arm down.");
			DisplayWrapper::GetInstance()->Output();
		}
		if(report.area > 0.8*XRESOLUTION*YRESOLUTION) { //If the peg takes up 80% of the camera, then stop.
			drive->Drive(0,0,0);
		}
	case Prepare:
		DisplayWrapper::GetInstance()->PrintfLine(4,"Reposition4Tele");
		DisplayWrapper::GetInstance()->Output();
	}
}


void BetaRobot::TeleopInit(void)
{
	pcvs->Start();
	time->Start();
}

void BetaRobot::TeleopPeriodic(void)
{
	
	//IO
	#ifdef USE_GYRO
	DisplayWrapper::GetInstance()->PrintfLine(0,"Gyro Angle: %f", gyro->GetAngle());
	#endif
	DisplayWrapper::GetInstance()->PrintfLine(1,"Clicks: %f", lift->Get());
	DisplayWrapper::GetInstance()->Output();
	
	//Drive
	float x, y;
	joystick->GetAxis(&x, &y);
	if (joystick->GetButton(highResButton))
	{
		drive->Drive(x/HIGH_RES_MULTIPLIER, y/HIGH_RES_MULTIPLIER, joystick->GetRotation()/HIGH_RES_MULTIPLIER);
	}
	else
	{
		drive->Drive(x, y, joystick->GetRotation());
	}
	
	//Set Arm Height
	if(joystick->GetButton(sideFirstButton)) {
		arm->setHeight(sideFirst);
	}
	else if(joystick->GetButton(middleFirstButton)) {
		arm->setHeight(middleFirst);
	}
	else if(joystick->GetButton(sideSecondButton)) {
		arm->setHeight(sideSecond);
	}
	else if(joystick->GetButton(middleSecondButton)) {
		arm->setHeight(middleSecond);
	}
	
	//Claw Toggle
	if(joystick->GetButton(trigger) && (time->Get()-triggerLockStart>1 || triggerRelease)) {
		arm->toggle();
		triggerLockStart=time->Get();
		triggerRelease=false;
	}
	else if (!joystick->GetButton(trigger))
	{
		triggerRelease=true;
	}
	
	//Shape Shift
	if(joystick->GetButton(shapeShifter) && (time->Get()-shapeLockStart>1 || shapeRelease)) {
		switch (arm->getShape())
		{
		case triangle:
			arm->setShape(circle);
		case circle:
			arm->setShape(square);
		case square:
			arm->setShape(triangle);
		}
		arm->setCenter(0);
		arm->setHeight(loadingLevel);
		shapeLockStart=time->Get();
		shapeRelease=false;
	}
	else if (!joystick->GetButton(shapeShifter))
	{
		shapeRelease=true;
	}
	
	//Reset Gyro
	#ifdef USE_GYRO
	if(joystick->GetButton(gyroResetButton)) {
		gyro->Reset();
	}
	#endif
	
	//Deploy
	if(joystick->GetButton(deployButton) && time->Get()>115) {
		mini->Deploy();
	}
	else
	{
		mini->StopDeploy();
	}
	
	//Vision Snapper
	if(joystick->GetButton(targetSnapButton)) {
		arm->snapToPeg();
	}
	
	//Arm Shifter
	float xpov,ypov;
	if (time->Get()-POVStart>0.03)
	{
		joystick->GetPov(&xpov,&ypov);
		arm->setCenter(arm->getCenter() + MANUAL_ARM_SHIFT_X * (int)xpov);
		arm->setHeight(arm->getHeight() + MANUAL_ARM_SHIFT_Y * (int)ypov);
		POVStart=time->Get();
	}
}

