#include "MyRobot.h"

BetaRobot::BetaRobot(void)
{
	joystick = new JoystickWrapper(1, Extreme3DPro);
	joystick->SetSnapPoints(8);
	drive = new DriverWrapper(Mecanum);
	lift = new Encoder(ARM_CHAIN_ENCODER_A_CHANNEL, ARM_CHAIN_ENCODER_B_CHANNEL);
	servo = new Servo(DIGITAL_SIDECAR_PORT,SERVO_CHANNEL_START);
	servo->SetSafetyEnabled(false);
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
	//Drive
	float x, y;
	joystick->GetAxis(&x, &y);
	drive->Drive(x, y, joystick->GetRotation());
	
	//IO
	#ifdef USE_GYRO
	DisplayWrapper::GetInstance()->PrintfLine(0,"Gyro Angle: %f", gyro->GetAngle());
	#endif
	DisplayWrapper::GetInstance()->PrintfLine(1,"Clicks: %f", lift->Get());
	DisplayWrapper::GetInstance()->Output();
	
	//Set Arm Height
	if(joystick->GetButton(sideFirstButton)) {
		arm->setHeight(sideFirst);
	}
	else if(joystick->GetButton(middleFirstButton)) {
		arm->setHeight(middleFirst);
	}
	else if(joystick->GetButton(loadingLevelButton)) {
		arm->setHeight(loadingLevel);
	}
	else if(joystick->GetButton(sideSecondButton)) {
		arm->setHeight(sideSecond);
	}
	else if(joystick->GetButton(middleSecondButton)) {
		arm->setHeight(middleSecond);
	}
	
	//Claw stuff
	if(joystick->GetButton(trigger) && time->Get()-triggerLockStart>0.7) {
		arm->toggle();
		triggerLockStart=time->Get();
	}
	if(joystick->GetButton(shapeShifter) && time->Get()-shapeLockStart>0.3) {
		switch (arm->getShape())
		{
		case triangle:
			arm->setShape(circle);
		case circle:
			arm->setShape(square);
		case square:
			arm->setShape(triangle);
		}
		arm->setHeight(loadingLevel);
		shapeLockStart=time->Get();
	}
	
	//Rare buttons
	#ifdef USE_GYRO
	if(joystick->GetButton(gyroResetButton)) {
		gyro->Reset();
	}
	#endif
	
	if(joystick->GetButton(deployButton) && time->Get()>115) {
		servo->Set(1.0);
	}
	else
	{
		servo->Set(0.0);
	}
}

