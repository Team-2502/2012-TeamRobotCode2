#ifndef DRIVETRAIN_H
#define DRIVETRAIN_H

#include <WPILib.h>

class Jaguar;

/**
 * The drivetrain of our Robot.
 */
class DriveTrain
{
public:
	DriveTrain();
	~DriveTrain();
	
	/**
	 * Drive arcade-style.
	 * 
	 * \param twist the turn speed.
	 * \param speed the speed/direction of the robot.
	 */
	void DriveArcade(double twist, double speed);
	
	/**
	 * Drive tank-style with two channels.
	 * 
	 * \param leftChannel the left wheel channel.
	 * \param rightChannel the right wheel channel.
	 */
	void DriveTank(double leftChannel, double rightChannel);
	
	void PIDWrite(float output);
	void ReservePrimaryLines();
	void ReserveSecondaryLines();
	void SetLeft(double value);
	void SetRight(double value);
	
	void setEnabled(bool enabled) { this->enabled = enabled; }
	
private:
	DisplayWriter primaryDisplay;
	DisplayWriter secondaryDisplay;

	Jaguar* left;
	Jaguar* right;
	RobotDrive* roboDrive;
	
	bool enabled;
};

#endif // DRIVETRAIN_H
