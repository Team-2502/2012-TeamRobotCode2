#include "Collector.h"
#include "DisplayWriter.h"
#include "DisplayWrapper.h"
#include "DriveTrain.h"
#include "JoystickWrapper.h"
#include "Logger.h"
#include "Robot.h"
#include "Singleton.h"
#include "squarefinder.h"
#include <time.h>
#include "SharpIR.h"
#include "Shooter.h"

bool Robot::operatorControlEnabled = false;
Robot* Robot::me = NULL;

Robot::Robot()
{
	me = this; // Coolest statement ever

	GetWatchdog().SetEnabled(false);

	speedMultiplier = 1.0;
	shotModifierX = 0;			// start with a count of left/right adjustment in .01 increments
	shotModifierZ = 0;			// start with a count of distance adjustments in 6" increments

	Logger* logger = new Logger("/ni-rt/system/logs/robot.txt");
	Singleton<Logger>::SetInstance(logger);

	vision = new Vision(new SquareFinder);
	vision->setEnabled(true); //Don't process without button.
	vision->start();
	Singleton<DriveTrain>::SetInstance(new DriveTrain);
	Singleton<Collector>::SetInstance(new Collector);
	Singleton<Collector>::GetInstance().Start();
	Singleton<Shooter>::SetInstance(new Shooter);

	// The order in which lines are reserved dictates the order
	// in which lines are displayed on the LCD.
	this->primaryDisplay.Reserve(1);
	COLLECTOR.reservePrimaryLines();
	SHOOTER.reservePrimaryLines();
	DRIVETRAIN.ReservePrimaryLines();
	VISION.reservePrimaryLines();
	SQUAREFINDER.reservePrimaryLines();

	// There is some additional information, secondary information,
	// that comes after all of the primary information.
	this->secondaryDisplay.Reserve(7);
	COLLECTOR.reserveSecondaryLines();
	SHOOTER.reserveSecondaryLines();
	DRIVETRAIN.ReserveSecondaryLines();
	VISION.reserveSecondaryLines();
	SQUAREFINDER.reserveSecondaryLines();

	Singleton<Logger>::GetInstance().Logf("Starting the Robot class.");

	operatorControlTask = new Task("2502OC", (FUNCPTR)OperatorControlLoop);

	//balanceAccelerometer = new AccelPID_Wrapper(new ADXL345_I2C(1)); //Takes ownership of ADXL345

	//balancePID = new PIDController(0.1,.01,0.0,balanceAccelerometer,&Singleton<DriveTrain>::GetInstance()); //\todo Tune these! No D.
	//balancePID->Disable();

	//gyro = new Gyro(1);
	//gyro->Reset();

	joystick1 = new JoystickWrapper(1, Extreme3DPro);
	//joystick2 = new JoystickWrapper(2, Attack3);
	joystickCallbackHandler = new JoystickCallback<Robot>(joystick1,this);
	joystickCallbackHandler->SetHeldCallback(RAMP_DOWN_BUTTON, GET_FUNC(RampDown));
	joystickCallbackHandler->SetHeldCallback(RAMP_UP_BUTTON, GET_FUNC(RampUp));
	joystickCallbackHandler->SetHeldCallback(EJECT_BALLS_BUTTON, GET_FUNC(CollectorEject));
	joystickCallbackHandler->SetUpCallback(RAMP_DOWN_BUTTON, GET_FUNC(RampOff));
	joystickCallbackHandler->SetUpCallback(RAMP_UP_BUTTON, GET_FUNC(RampOff));
	joystickCallbackHandler->SetTriggerDownCallback(GET_FUNC(ShootBasketTeleoperated));
	joystickCallbackHandler->SetHeldCallback(TURRET_BUTTON, GET_FUNC(MoveTurret));
	joystickCallbackHandler->SetUpCallback(TURRET_BUTTON, GET_FUNC(TurretOff));

	//joystickCallbackHandler->SetHeldCallback(9, GET_FUNC(RatioDown));
	//joystickCallbackHandler->SetHeldCallback(10, GET_FUNC(RatioUp));

	// Change Ball Count
	joystickCallbackHandler->SetDownCallback(COLLECTOR_ADD_BALL_BUTTON, GET_FUNC(CollectorIncBall));
	joystickCallbackHandler->SetDownCallback(COLLECTOR_SUB_BALL_BUTTON, GET_FUNC(CollectorDecBall));

	joystickCallbackHandler->SetHeldCallback(9, GET_FUNC(MediumSpeedOn));
	joystickCallbackHandler->SetHeldCallback(11, GET_FUNC(SlowSpeedOn));
	joystickCallbackHandler->SetUpCallback(9, GET_FUNC(NormalSpeed));
	joystickCallbackHandler->SetUpCallback(11, GET_FUNC(NormalSpeed));
	joystickCallbackHandler->SetHeldCallback(4, GET_FUNC(forceDriveOn));

	//joystickCallbackHandler->SetDownCallback(BalanceRobot,GET_FUNC(BalanceRobotOn));
	//joystickCallbackHandler->SetUpCallback(BalanceRobot,GET_FUNC(BalanceRobotOff));
}
//Robot used to be 5200B processor.
Robot::~Robot()
{
	Singleton<Logger>::GetInstance().Logf("Shutting down the Robot class.");

	//Destroy instances of singletons that we have used
	Singleton<Collector>::DestroyInstance();
	Singleton<DisplayWrapper>::DestroyInstance();
	Singleton<DriveTrain>::DestroyInstance();
	Singleton<Logger>::DestroyInstance();
	Singleton<Shooter>::DestroyInstance();

	delete joystickCallbackHandler;
	delete operatorControlTask;

	//delete balancePID;
	//delete balanceAccelerometer;

	me = NULL;
}

void Robot::forceDriveOn()
{
	DRIVETRAIN.setEnabled(true);
}

void Robot::RampDown()
{
	ROBOT.primaryDisplay.PrintfLine(0, "Ramp Going Down");
	Singleton<Collector>::GetInstance().ManipulateRamp(DOWN);
}

void Robot::RampUp()
{
	ROBOT.primaryDisplay.PrintfLine(0, "Ramp Going Up");
	Singleton<Collector>::GetInstance().ManipulateRamp(UP);
}

void Robot::CollectorIncBall()
{
	Singleton<Collector>::GetInstance().ChangeBallCountBy(1);
}

void Robot::CollectorDecBall()
{
	Singleton<Collector>::GetInstance().ChangeBallCountBy(-1);
}

double Robot::shotDirectionModifier()
{
	// offset in hundredths left or right of target
	return shotModifierX * .01;
}

double Robot::shotDistanceModifier()
{
	// offset in 6" distance increments
	return shotModifierZ * 0.5;
}

void Robot::ShotXInc()
{
	shotModifierX += 1;
}

void Robot::ShotXDec()
{
	shotModifierX -= 1;
}

void Robot::ShotZInc()
{
	shotModifierZ += 1;
}

void Robot::ShotZDec()
{
	shotModifierZ -= 1;
}


void Robot::RampOff()
{
	ROBOT.primaryDisplay.PrintfLine(0, "Ramp Turning Off");
	Singleton<Collector>::GetInstance().ManipulateRamp(RAMP_OFF);
}

void Robot::CollectorEject()
{
	ROBOT.primaryDisplay.PrintfLine(0, "Ejecting Ball");
	Singleton<Collector>::GetInstance().Eject();
}

void Robot::Autonomous()
{
	Singleton<Logger>::GetInstance().Logf("Starting Autonomous Mode.");
	Singleton<Collector>::GetInstance().SetBallCount( 2); // preloaded with 2 balls in autonomous

	primaryDisplay.PrintfLine(0, "Shooting 2");
	ShootBasket( 2 );

	KinectStick leftStick(1);
	KinectStick rightStick(2);

	Timer displayUpdateFrequency;
	displayUpdateFrequency.Start();

	primaryDisplay.PrintfLine(0, "Kinect Controls");
	while (IsAutonomous() )
	{
		secondaryDisplay.PrintfLine(1, "Shot-Dir: %.2f", shotDirectionModifier());
		secondaryDisplay.PrintfLine(2, "Shot-Dist: %.1f\"", shotDistanceModifier());

		DRIVETRAIN.SetLeft(-leftStick.GetY());
		DRIVETRAIN.SetRight(rightStick.GetY());
		if (leftStick.GetRawButton(1) ) // Left Leg Out
		{
			primaryDisplay.PrintfLine(0, "Ramp UP");
			RampUp();
		}

		if (leftStick.GetRawButton(2) ) // Right Leg Out
		{
			primaryDisplay.PrintfLine(0, "Ramp DOWN");
			RampDown();
		}

		if ( !leftStick.GetRawButton(1) && !leftStick.GetRawButton(2) ) // both legs in
			RampOff();

		// The Joystick Throttle controls the scrolling of the display
		// The display is updated at a controlled pace
		DisplayWrapper::GetInstance()->SetScrollLocation(joystick1->GetThrottle());
		if (displayUpdateFrequency.HasPeriodPassed(1.0 / 5)) {
			secondaryDisplay.PrintfLine(1, "Shot-Dir: %.2f", shotDirectionModifier());
			secondaryDisplay.PrintfLine(2, "Shot-Dist: %.1f\'", shotDistanceModifier());

			displayUpdateFrequency.Reset();
			DisplayWrapper::GetInstance()->Output();
		}

		Wait(0.1);
	}

	Singleton<Logger>::GetInstance().Logf("Stopping Autonomous Mode.");
}

void Robot::OperatorControl()
{
	LOGGER.Logf("Starting operator control.");

	operatorControlEnabled = true;
	operatorControlTask->Start();
	while ( IsOperatorControl() ) 
	{
		float x, y, rot;
		me->joystick1->GetAxis(&x, &y);
		rot = me->joystick1->GetRawRotation();

		if ( !me->joystick1->GetButton(TURRET_BUTTON) )
			DRIVETRAIN.DriveArcade(me->speedMultiplier*rot, me->speedMultiplier * cubicFilter(-y));

		me->secondaryDisplay.PrintfLine(2, "X/Y/R: %f/%f/%f", x, y, rot);
		me->secondaryDisplay.PrintfLine(3, "rps:%f", ((me->joystick1->GetThrottle() + 1.0) / 2.0) * 15.0 + 20.0);
		me->secondaryDisplay.PrintfLine(4, "ratio:%f", Singleton<Shooter>::GetInstance().GetTopRatio());

		//This thread NEEDS to run at all times for network communication! DO NOT REMOVE THIS!
		Wait(0.01);
	}
	operatorControlEnabled = false;
	Wait(0.5);
	operatorControlTask->Stop();
	LOGGER.Logf("Stopping operator control.");
}

void Robot::OperatorControlLoop()
{
	Timer displayUpdateFrequency;
	displayUpdateFrequency.Start();

	ROBOT.primaryDisplay.PrintfLine(0, "Joystick Controls");

	while( operatorControlEnabled )
	{
		DRIVETRAIN.setEnabled(true);
		me->joystickCallbackHandler->Update(); //long call.

		double offset, distance;
		Singleton<Vision>::GetInstance().FindTarget(offset, distance);
		me->secondaryDisplay.PrintfLine(5, "Speed:%f", SIGN(offset)*.15+.1*offset);
		me->secondaryDisplay.PrintfLine(6, "Vis:%1.4f,%1.4", distance, offset);

		SHOOTER.Update();

		// The display is updated at a controlled pace
		if (displayUpdateFrequency.HasPeriodPassed(1.0 / 5)) 
		{
			// this is a convenient time to check the HAT for shot adjustments
			float xaxis, yaxis;
			me->joystick1->GetPov(&xaxis, &yaxis);
			if (xaxis < 0)
				me->ShotXDec();
			if (xaxis > 0)
				me->ShotXInc();
			if (yaxis < 0)
				me->ShotZDec();
			if (yaxis > 0)
				me->ShotZInc();

			displayUpdateFrequency.Reset();

			me->secondaryDisplay.PrintfLine(1, "Shot-Dir: %.2f", me->shotDirectionModifier());
			me->secondaryDisplay.PrintfLine(2, "Shot-Dist: %.1f\'", me->shotDistanceModifier());

			// The Joystick Throttle controls the scrolling of the display
			DisplayWrapper::GetInstance()->SetScrollLocation(-1.0 * me->joystick1->GetThrottle());

			// update the LCD
			DisplayWrapper::GetInstance()->Output();
		}

		Wait(0.01);
	}
}

void Robot::BalanceRobotOff()
{
	balancePID->Disable();
}

void Robot::BalanceRobotOn()
{
	balancePID->Enable();
	balancePID->SetSetpoint(0.0);
}

void Robot::ShootBasketTeleoperated()
{
	ShootBasket( 0 );
}

void Robot::ShootBasket( int shots )
{
	double offset = 0.0;
	double distance = 0.0;
	Shooter& shooter = Singleton<Shooter>::GetInstance();
	Collector& collector = Singleton<Collector>::GetInstance();
	Vision& vision = Singleton<Vision>::GetInstance();

	// disable the drive
	DRIVETRAIN.setEnabled(false);

	collector.PrepareToShoot();

	Timer alignTimer;
	alignTimer.Start();
	int count = 0;
	
	double averageDistance = 0.0;
	
//#define DEMO_MODE // we are demoing shooting without targets
#ifndef DEMO_MODE
/*
	while(!alignTimer.HasPeriodPassed(3.5) && (joystick1->GetJoystick()->GetRawButton(1) || shots > 0)) //Shots==0 -> teleop
	{
		vision.FindTarget(offset, distance);
		offset += shotDirectionModifier();
		distance += shotDistanceModifier();

		ROBOT.secondaryDisplay.PrintfLine(5, "Speed:%f", (SIGN(offset)*-0.175));
		ROBOT.secondaryDisplay.PrintfLine(6, "Vis:%1.4f,%1.4", offset, distance);
		DisplayWrapper::GetInstance()->Output();
		if (fabs(offset) < 0.02 && distance != 0)
		{
			averageDistance += distance;
			count++;
			if( count >= 10 )
				break;
		}
		shooter.SetTurret((SIGN(offset)*-0.175));
		Wait(0.05);
		shooter.SetTurret(0.0);
		if( fabs(offset) <= .2)
			Wait(.2 - fabs(offset));
	}
	shooter.SetTurret(0.0);
	
	averageDistance /= (double) count;
	distance = averageDistance;

	// if timer expired or the user has released the trigger button
	if (alignTimer.HasPeriodPassed(3.5) || ( !joystick1->GetJoystick()->GetRawButton(1) && shots == 0 )) { //shots==0==not auto
		DRIVETRAIN.setEnabled(true); //Fix
		return;
	}
*/
#else
	// temporary for demo
	distance = (me->joystick1->GetThrottle() + 1.0) / 2.0 * 34.0 + 16.0;
#endif // DEMO_MODE
	
	shooter.ShootBasket(distance, joystick1->GetJoystick() , shots );
	//shooter.SetTopRatio(1.0);
	//shooter.Shoot(27.7, joystick1->GetJoystick(), shots);
	DRIVETRAIN.setEnabled(true);
}

void Robot::MoveTurret()
{
	float rot = joystick1->GetRawRotation() / -2.0;
	Singleton<Shooter>::GetInstance().SetTurret(rot);
	Singleton<DriveTrain>::GetInstance().DriveArcade(0.0, 0.0);
}

void Robot::TurretOff()
{
	SHOOTER.SetTurret(0);
}

void Robot::MediumSpeedOn()
{
	speedMultiplier = 0.6;
}

void Robot::SlowSpeedOn()
{
	speedMultiplier = 0.4;
}

void Robot::NormalSpeed()
{
	speedMultiplier = 1.0;
}

void Robot::RatioDown()
{
	SHOOTER.SetTurretRatio(SHOOTER.GetTurretRatio() * 0.995);
}

void Robot::RatioUp()
{
	SHOOTER.SetTurretRatio(SHOOTER.GetTurretRatio() * 1.005);
}

START_ROBOT_CLASS(Robot)
