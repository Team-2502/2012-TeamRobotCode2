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

/**
 * This wraps around the Joystick to provide additional functionality.
 */
class JoystickWrapper
{
public:
	JoystickWrapper(int port, StickType type);
	~JoystickWrapper();
	
	float GetAngle() const; //In Degrees.
	Joystick* GetJoystick() {return this->joystick;}
	float GetMagnitude() const;
	void GetPov(float* xaxis, float* yaxis) const;
	int GetPovAngle() const;
	void GetAxis(float* xaxis, float* yaxis) const;
	void GetRawAxis(float* xaxis, float* yaxis) const;
	float GetRotation() const;
	float GetRawRotation() const;
	float GetThrottle() const;
	StickType GetType() const { return this->type; }
	void SetSnapPoints(int snapPoints) {this->snapPoints = snapPoints;}
	bool GetButton(int buttonID);
	
private:
	Joystick* joystick;
	int snapPoints;
	StickType type;
};

#endif // JOYSTICKWRAPPER_H
