#include <math.h>

#include "Constants.h"
#include "Logger.h"
#include "Math.h"
#include "Shooter.h"
#include "Singleton.h"
#include "Collector.h"
#include "DisplayWriter.h"
#include "DisplayWrapper.h"

void Shooter::reservePrimaryLines() { primaryDisplay.Reserve(1); }
void Shooter::reserveSecondaryLines() { secondaryDisplay.Reserve(3); }

Shooter::Shooter() :
		turretDirection(0.0),
		topRatio(1.0),
		turretRatio(0.607)
{
	Singleton<Logger>::GetInstance().Logf("Shooter: Starting up...");
	//Setup Jaguars
	topJag = new Jaguar(DIGITAL_SIDECAR_SLOT, SHOOTER_TOP_JAG_CHANNEL);
	bottomJag = new Jaguar(DIGITAL_SIDECAR_SLOT, SHOOTER_BOTTOM_JAG_CHANNEL);
	turretVictor = new Victor(TURRET_CHANNEL);
	topEncoder = new SingleChannelEncoder(SHOOTER_TOP_ENCODER_A, *topJag );
	bottomEncoder = new SingleChannelEncoder(SHOOTER_BOTTOM_ENCODER_A, *bottomJag);
	turretEncoder = new Encoder(TURRET_ENCODER_A, TURRET_ENCODER_B);
	
	topPID = new PIDController(.12, .013, 0.0, topEncoder, topJag);
	bottomPID = new PIDController(.12, .013 * 2, 0.0, bottomEncoder, bottomJag);
	
	topEncoder->Reset();
	topEncoder->Start();
	bottomEncoder->Reset();
	bottomEncoder->Start();
	
	topPID->SetSetpoint(0);
	bottomPID->SetSetpoint(0);
	
	double pulseDistance = (TURRET_WHEEL_DIAMETER / TURRET_LAZY_SUSAN_DIAMETER) * 360.0 / (double)TURRET_ENCODER_PULSES;
	turretEncoder->SetDistancePerPulse(pulseDistance);
	turretEncoder->Start(); // This should be running at all times
}

Shooter::~Shooter()
{
	Singleton<Logger>::GetInstance().Logf("Shooter: Shutting down...");
	
	turretEncoder->Stop();
	
	delete topJag;
	delete bottomJag;
	delete turretVictor;
	delete turretIR;
	delete topEncoder;
	delete bottomEncoder;
	delete turretEncoder;
	delete topPID;
	delete bottomPID;
}

void Shooter::Shoot(double speed , Joystick* joystick, int shots )
{
	Collector& collector = Singleton<Collector>::GetInstance();
	
	topPID->Enable();
	bottomPID->Enable();
	
	topPID->SetSetpoint(-1.0 * topRatio * speed);
	bottomPID->SetSetpoint(-1.0 * speed);
	
    do
    {
	    int count = 0;
	    int limiter = 0;
	    // wait for shooter to get up to speed as long as they are still pushing the trigger
        while( count < 10 && limiter < 750 && ( joystick->GetRawButton(1) || shots > 0))
	    {
		    if( (fabs(bottomEncoder->GetRate() - speed) <= 0.25 ) && (fabs(topEncoder->GetRate() - (topRatio * speed)) <= 0.25 ) )
			    count++;
		    else
			    count = 0;
		    secondaryDisplay.PrintfLine(0, "TopRate:%.3f", SHOOTER.topEncoder->GetRate());
		    secondaryDisplay.PrintfLine(1, "BotRate:%.3f", SHOOTER.bottomEncoder->GetRate());
			DisplayWrapper::GetInstance()->Output();
		    Wait(0.01);
		    limiter++;
	    }
        if( joystick->GetRawButton(1) || shots > 0 )
        {
            collector.Shoot();
            shots--;
        }

    } while ( joystick->GetRawButton(1) || shots > 0 ); // while joystick trigger is pressed, continue firing
    
    topPID->SetSetpoint(0);
	bottomPID->SetSetpoint(0);
	
	topPID->Disable();
	bottomPID->Disable();

	bottomJag->Set(0.0);
	topJag->Set(0.0);
}

void Shooter::ShootBasket(double distance, Joystick* joystick, int shots )
{
	if(distance < 1.0 || distance > 60.0) //If bad data, default to key.
		distance = 16.0;
	double spin = 1.827142857e-2 * distance - 0.19;
	if( spin != spin ) // if nan
		spin = 1.827142857e-2 * 16 - 0.19;
	SetTopRatio(spin);
	
	/*
	// Waiting for the top to stop moving
	while ( topEncoder->GetRate() != 0 )
	{
		topEncoder->PIDGet();
		Wait(0.1);
	}
	*/
	Shoot(27.7, joystick, shots );
}
void Shooter::SetPID(double p, double i, double d)
{
	this->bottomPID->SetPID(p, i, d);
	this->topPID->SetPID(p, i, d);
}

void Shooter::SetTopRatio(double ratio)
{
	topRatio = ratio;
	if( topRatio > 1.0 )
		topRatio = 1.0;
}

void Shooter::SetTurret(double direction)
{
	turretDirection = direction;
	this->turretVictor->Set( -1.0 * turretRatio * direction );
}

void Shooter::SetTurretRatio(double ratio)
{
	turretRatio = ratio;
	primaryDisplay.PrintfLine(0, "R:%f", turretRatio);
}

void Shooter::Update()
{
	double rotation = turretEncoder->GetDistance();
	if( (rotation < -90 && turretDirection < 0)  || (rotation > 90 && turretDirection > 0) )
		SetTurret(0);
	
	topEncoder->PIDGet();
	bottomEncoder->PIDGet();
    SHOOTER.secondaryDisplay.PrintfLine(0, "TopRate:%.3f", SHOOTER.topEncoder->GetRate());
    SHOOTER.secondaryDisplay.PrintfLine(1, "BotRate:%.3f", SHOOTER.bottomEncoder->GetRate());
}
