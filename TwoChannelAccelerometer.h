/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#ifndef TCACCELEROMETER_H_
#define TCACCELEROMETER_H_

#include "AnalogChannel.h"
#include "SensorBase.h"
#include "PIDSource.h"

/** 
 * Handle operation of the accelerometer.
 * The accelerometer reads acceleration directly through the sensor. Many sensors have
 * multiple axis and can be treated as multiple devices. Each is calibrated by finding
 * the center value over a period of time.
 */
class TwoChannelAccelerometer : public SensorBase
{
public:
	explicit TwoChannelAccelerometer();
	virtual ~TwoChannelAccelerometer();

	float GetAccelerationX();
	float GetAccelerationY();
	
	void SetXSensitivity(float sensitivity);
	void SetYSensitivity(float sensitivity);
	void SetXZero(float zero);
	void SetYZero(float zero);

private:
	void InitAccelerometer();

	AnalogChannel *m_analogChannelX;
	AnalogChannel *m_analogChannelY;
	float m_voltsPerG_x;
	float m_voltsPerG_y;
	float m_zeroGVoltageX;
	float m_zeroGVoltageY;
	bool m_allocatedChannel;
};

#endif

