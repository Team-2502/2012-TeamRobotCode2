#ifndef LSM303_I2C_H
#define LSM303_I2C_H

#include "SensorBase.h"

class I2C;

class LSM303_I2C : public SensorBase
{
private:
	static const UINT8 accelAddressR = 0x18;
	static const UINT8 accelAddressW = 0x18;
	static const UINT8 magAddress    = 0x3D;
	
	static const UINT8 accelPowerOn = 0x27; //001,10,111
	static const UINT8 accelData    = 0x40;
	
	static const UINT8 magSpeed      = 0x14;
	static const UINT8 magContinuous = 0x00;
	
	enum ControlRegister { CRA_REG_M = 0x00, MR_REG_M = 0x02,
	                       CTRL_REG1_A = 0x20, CTRL_REG2_A = 0x21,
                           CTRL_REG3_A = 0x22, CTRL_REG4_A = 0x23 };
	enum AccelRegisters  { OUT_X_L_A = 0x28,
	                       OUT_X_H_A = 0x29,
	                       OUT_Y_L_A = 0x2A,
	                       OUT_Y_H_A = 0x2B,
	                       OUT_Z_L_A = 0x2C,
	                       OUT_Z_H_A = 0x2D };
    enum MagRegisters    { OUT_X_H_M = 0x03,
                           OUT_X_L_M = 0x04,
                           OUT_Y_H_M = 0x05,
                           OUT_Y_L_M = 0x06,
                           OUT_Z_H_M = 0x07,
                           OUT_Z_L_M = 0x08 };
	/*enum MagRegisters    { OUT_X_H_M = 0x28,
	                       OUT_X_L_M = 0x29,
	                       OUT_Y_H_M = 0x2A,
	                       OUT_Y_L_M = 0x2B,
	                       OUT_Z_H_M = 0x2C,
	                       OUT_Z_L_M = 0x2D };*/

public:
	struct AxesReport
	{
		int XAxis;
		int YAxis;
		int ZAxis;
	};

public:
	explicit LSM303_I2C(UINT32 slot);
	virtual ~LSM303_I2C();
	AxesReport GetAccelerations();
	AxesReport GetMagnetic();

private:
	I2C* accelI2C_r;
	I2C* accelI2C_w;
	I2C* magI2C;
};

#endif

