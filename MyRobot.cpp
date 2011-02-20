#include <math.h>
#include <Dashboard.h>
#include "WPILib.h"

#include "DisplayWrapper.h"
#include "DriverWrapper.h"
#include "JoystickWrapper.h"
#include "Arm.h"
#include "Vision/PCVideoServer.h"

enum AutonomousState {
	TrackLine,
	PlaceTube,
	Prepare
};

class BetaRobot : public IterativeRobot
{
	public:
		BetaRobot(void)
		{
			joystick = new JoystickWrapper(1, Extreme3DPro);
			joystick->SetSnapPoints(8);
			drive = new DriverWrapper(Mecanum);
			lift = new Encoder(ARM_CHAIN_ENCODER_A_CHANNEL, ARM_CHAIN_ENCODER_B_CHANNEL);
			servo = new Servo(DIGITAL_SIDECAR_PORT,SERVO_CHANNEL_START);
			servo->SetSafetyEnabled(false);
			gyro = new Gyro(GYRO_SLOT,GYRO_CHANNEL);
			arm = new Arm();
			pcvs = new PCVideoServer;
			myState = PlaceTube;
		}
	
		void RobotInit(void) {}
		void DisabledInit(void) {pcvs->Stop();}
		void AutonomousInit(void) {}
		void TeleopInit(void) {pcvs->Start();}
		void AutonomousPeriodic(void)
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
		void TeleopPeriodic(void)
		{
			float x, y;
			joystick->GetAxis(&x, &y);
			drive->Drive(x, y, joystick->GetRotation());
			
			DisplayWrapper::GetInstance()->PrintfLine(0,"Gyro Angle: %f", gyro->GetAngle());
			DisplayWrapper::GetInstance()->PrintfLine(1,"Clicks: %f", lift->Get());
			DisplayWrapper::GetInstance()->Output();
			
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
			
			if(joystick->GetButton(11)) {
				servo->Set(1.0);
			}
			else if(joystick->GetButton(12)) {
				servo->Set(0);
			}

		}
		
		/** Unused functions */
		void DisabledPeriodic(void) {}
		void DisabledContinuous(void) {}
		void AutonomousContinuous(void) {}
		void TeleopContinuous(void) {}
		
	private:
		JoystickWrapper* joystick;
		DriverWrapper* drive;
		Encoder* lift;
		Servo* servo;
		Gyro* gyro;
		Arm *arm;
		PCVideoServer* pcvs;
		AutonomousState myState;
		Vision* eye;
};

START_ROBOT_CLASS(BetaRobot);
