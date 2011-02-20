#ifndef JOYSTICKWRAPPER_H
#define JOYSTICKWRAPPER_H

#include <WPILib.h>

/**
 * Stick types.
 *
 * Extreme3D
 *	Direction			Channel		Value
 *	Left				1	X		-
 *	Right				1	X		+
 *	Forward 			2	Y		-
 *	Backward			2	Y		+
 *	Counterclockwise	3	Z		-
 *	Clockwise			3	Z		+
 *	Throttle Up			4	Tw		-
 *	Throttle Down		4	Tw		+
 *	POV Left			5	NA		-
 *	POV Right			5	NA		+
 *	POV	Up				6	NA		-
 *	POV Down			6	NA		+
 *
 * Attack3
 *	Direction			Channel		Value
 *	Left				1	X		-
 *	Right				1	X		+
 *	Forward 			2	Y		-
 *	Backward			2	Y		+
 *	Throttle Up			4	Z/Th	-
 *	Throttle Down		4	Z/Th	+
 *
 * Dual Action
 *	Direction			Channel		Value
 *	Leftstick Left		1	X		-
 *	Leftstick Right		1	X		+
 *	Leftstick Forward 	2	Y		-
 *	Leftstick Backward	2	Y		+
 *	Rightstick Left		3	Z/Th	-
 *	Rightstick Right	3	Z/Th	+
 *	Rightstick Forward 	4	Tw		-
 *	Rightstick Backward 4	Tw		+
 */
enum StickType
{
	Extreme3DPro,
	Attack3,
	DualAction
};

enum Direction
{
	NORTH = 0,
	NORTHEAST = 45,
	EAST = 90,
	SOUTHEAST = 135,
	SOUTH = 180,
	SOUTHWEST = 225,
	WEST = 270,
	NORTHWEST = 315,
};

enum Button
{
	trigger=1,
	shapeShifter=2,
	sideFirstButton=3,
	middleFirstButton=4,
	loadingLevelButton=12,
	sideSecondButton=5,
	middleSecondButton=6,
	deployButton=7,
	gyroResetButton=8
};

/**
 * This wraps around the Joystick to provide additional functionality.
 */
class JoystickWrapper
{
public:
	JoystickWrapper(int port, StickType type);
	
	/**
	 * Get the angle of the joystick in degrees.
	 */
	float GetAngle() const;
	
	/**
	 * Get the instance of the Joystick that it wraps around.
	 */
	Joystick* GetJoystick() {return this->joystick;}
	
	/**
	 * Get the magnitude of the joystick.
	 */
	float GetMagnitude() const;
	
	/**
	 * Get the pov values from the joystick.
	 */
	void GetPov(float* xaxis, float* yaxis) const;
	
	/**
	 * Get the angle of the pov from the joystick. North is zero and it progresses clockwise.
	 */
	int GetPovAngle() const;
	
	/**
	 * Get a value of both Joystick axis from -1.0 to 1.0. This uses the snapping
	 * feature and also only works for the x and y axis.
	 */
	void GetAxis(float* xaxis, float* yaxis) const;
	
	/**
	 * This gets the raw axis from the joystick without snapping.
	 */
	void GetRawAxis(float* xaxis, float* yaxis) const;
	
	/**
	 * This returns the rotation value of the joystick.
	 */
	float GetRotation() const;
	
	/**
	 * This returns the raw rotation value of the joystick without filtering.
	 */
	float GetRawRotation() const;
	
	/**
	 * Get the value of the throttle. It goes from -1.0 at the bottom to 1.0 at the top.
	 */
	float GetThrottle() const;
	
	/**
	 * Set the number of snap points on the joystick. The higher the number,
	 * the more precise that it will be, but the more sensitive it will
	 * be as well.
	 */
	void SetSnapPoints(int snapPoints) {this->snapPoints = snapPoints;}
	
	/**
	 * Get the status of button # i.
	 */
	bool GetButton(int i) const;
	
private:
	Joystick* joystick;
	int snapPoints;
	StickType type;
};

#endif // JOYSTICKWRAPPER_H
