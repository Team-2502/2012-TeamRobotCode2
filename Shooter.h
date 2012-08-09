#ifndef SHOOTER_H
#define SHOOTER_H

#include <WPILib.h>
#include "DisplayWriter.h"
#include "SharpIR.h"
#include "SingleChannelEncoder.h"

class Shooter
{
public:
	Shooter();
	~Shooter();
	
	double GetTopRatio() const { return topRatio; }
	double GetTurretRatio() const { return turretRatio; }
	void SetPID(double p, double i, double d);
	void SetTopRatio(double ratio);
	void SetTurret(double direction);
	void SetTurretRatio(double ratio);
	void Shoot(double speed, Joystick* joyStick, int shots );
	void ShootBasket(double distance, Joystick* joyStick, int shots );
	void Update();
	
	void reservePrimaryLines();
	void reserveSecondaryLines();
	
private:
	DisplayWriter			primaryDisplay;
	DisplayWriter			secondaryDisplay;
	double 					turretDirection;
	Jaguar* 				bottomJag;
	Jaguar* 				topJag;
	PIDController*			bottomPID;
	PIDController*			topPID;
	SingleChannelEncoder*	bottomEncoder;
	SingleChannelEncoder*	topEncoder;
	Encoder*				turretEncoder;
	Victor* 				turretVictor;
	SharpIR*				turretIR;
	double					topRatio;
	double					turretRatio;
};

#endif // SHOOTER_H
