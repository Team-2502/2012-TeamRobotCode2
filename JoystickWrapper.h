#ifndef JOYSTICKWRAPPER_H
#define JOYSTICKWRAPPER_H

#include <WPILib.h>

/**
 * Stick types.
 */
enum StickType
{
	Extreme3DPro,
	Attack3,
	DualAction,
};

/**
 * This wraps around the Joystick to provide additional functionality.
 */
class JoystickWrapper
{
public:
	JoystickWrapper(int number, StickType type);
	
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
	 * Get the value of the throttle. It goes from -1.0 at the bottom to 1.0 at the top.
	 */
	float GetThrottle() const;
	
	/**
	 * Set the number of snap points on the joystick. The higher the number,
	 * the more precise that it will be, but the more sensitive it will
	 * be as well.
	 */
	void SetSnapPoints(int snapPoints) {this->snapPoints = snapPoints;}
	
private:
	Joystick* joystick;
	int snapPoints;
	StickType type;
};

#endif // JOYSTICKWRAPPER_H
