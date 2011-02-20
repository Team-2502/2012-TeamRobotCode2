#include <math.h>
#include <Dashboard.h>
#include "WPILib.h"

#include "DisplayWrapper.h"
#include "DriverWrapper.h"
#include "JoystickWrapper.h"

class BetaRobot : public IterativeRobot
{
	public:
		BetaRobot(void)
		{
			joystick = new JoystickWrapper(1, Extreme3DPro);
			joystick->SetSnapPoints(8);
			driver = new DriverWrapper(Mecanum);
			lift = new Encoder(ARM_CHAIN_ENCODER_A_CHANNEL, ARM_CHAIN_ENCODER_B_CHANNEL);
			servo = new Servo(DIGITAL_SIDECAR_PORT,SERVO_CHANNEL_START);
			servo->SetSafetyEnabled(false);
			gyro = new Gyro(GYRO_SLOT,GYRO_CHANNEL);
			arm = new Arm();
		}
	
		void RobotInit(void) {}
		void DisabledInit(void) {pcvs->Stop();}
		void AutonomousInit(void) {}
		void TeleopInit(void) {pcvs->Start();}
		void AutonomousPeriodic(void) {}
		
		void TeleopPeriodic(void)
		{
			float x, y;
			joystick[joy]->GetAxis(&x, &y);
			driver->Drive(x, y, joystick[0]->GetRotation());
			
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
		DriverWrapper* driver;
		Encoder* lift;
		Servo* servo;
		Gyro* gyro;
		Arm *arm
};

START_ROBOT_CLASS(BetaRobot);
