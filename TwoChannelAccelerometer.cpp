/*----------------------------------------------------------------------------*/
/* Copyright (c) FIRST 2008. All Rights Reserved.							  */
/* Open Source Software - may be modified and shared by FRC teams. The code   */
/* must be accompanied by the FIRST BSD license file in $(WIND_BASE)/WPILib.  */
/*----------------------------------------------------------------------------*/

#include <cmath>
#include "TwoChannelAccelerometer.h"
#include "AnalogModule.h"
#include "Utility.h"
#include "WPIStatus.h"

/**
 * Common function for initializing the accelerometer.
 */
void TwoChannelAccelerometer::InitAccelerometer()
{
	m_zeroGVoltageX = 2.35;
	m_zeroGVoltageY = 2.40;
	m_voltsPerG_x = 3.18;
	m_voltsPerG_y = 3.11;
}

/**
 * Create new instance of accelerometer.
 * 
 * Make a new instance of the accelerometer given a module and channel. The constructor allocates
 * the desired analog channel from the specified module
 */
TwoChannelAccelerometer::TwoChannelAccelerometer(UINT32 slot, UINT32 channelX, UINT32 channelY)
{
	m_analogChannelX = new AnalogChannel(slot, channelX);
	m_analogChannelY = new AnalogChannel(slot, channelY);
	m_allocatedChannel = true;
	InitAccelerometer();
}

/**
 * Delete the analog components used for the accelerometer.
 */
TwoChannelAccelerometer::~TwoChannelAccelerometer()
{
	if (m_allocatedChannel)
	{
		delete m_analogChannelX;
		delete m_analogChannelY;
	}
}

/**
 * Return the acceleration in Gs.
 * 
 * The acceleration is returned units of Gs.
 * 
 * @return The current acceleration of the sensor in Gs.
 */
float TwoChannelAccelerometer::GetAccelerationX()
{
	return (m_analogChannelX->GetAverageVoltage() - m_zeroGVoltageX) / (m_voltsPerG_x-m_zeroGVoltageX);
}

float TwoChannelAccelerometer::GetAccelerationY()
{
	return (m_analogChannelY->GetAverageVoltage() - m_zeroGVoltageY) / (m_voltsPerG_y-m_zeroGVoltageY);
}

/**
 * Set the accelerometer sensitivity.
 * 
 * This sets the sensitivity of the accelerometer used for calculating the acceleration.
 * The sensitivity varys by accelerometer model. There are constants defined for various models.
 * 
 * @param sensitivity The sensitivity of accelerometer in Volts per G.
 */
void TwoChannelAccelerometer::SetXSensitivity(float sensitivity)
{
	m_voltsPerG_x = sensitivity;
}

void TwoChannelAccelerometer::SetYSensitivity(float sensitivity)
{
	m_voltsPerG_y = sensitivity;
}

/**
 * Set the voltage that corresponds to 0 G.
 * 
 * The zero G voltage varys by accelerometer model. There are constants defined for various models.
 * 
 * @param zero The zero G voltage.
 */
void TwoChannelAccelerometer::SetXZero(float zero)
{
	m_zeroGVoltageX = zero;
}

void TwoChannelAccelerometer::SetYZero(float zero)
{
	m_zeroGVoltageY = zero;
}
