#include "LSM303_I2C.h"
#include "DigitalModule.h"
#include "I2C.h"
#include "Utility.h"

LSM303_I2C::LSM303_I2C(UINT32 slot) : accelI2C_r(NULL), accelI2C_w(NULL), magI2C(NULL)
{
	DigitalModule *module = DigitalModule::GetInstance(slot);
	accelI2C_r = module->GetI2C(accelAddressR);
	accelI2C_w = module->GetI2C(accelAddressW);
	magI2C = module->GetI2C(magAddress);

	// Turn on the accelerometer
	accelI2C_w->Write(CTRL_REG1_A, accelPowerOn);
	// Set up accelerometer data format.
	accelI2C_w->Write(CTRL_REG4_A, accelData);

	// Speed up the magnetic sensor
	magI2C->Write(CRA_REG_M, magSpeed);
	// Wake up the magnetic sensor
	magI2C->Write(MR_REG_M, magContinuous);
}

LSM303_I2C::~LSM303_I2C()
{
	delete accelI2C_r;
	accelI2C_r = NULL;
	delete accelI2C_w;
	accelI2C_w = NULL;
	delete magI2C;
	magI2C = NULL;
}

LSM303_I2C::AxesReport LSM303_I2C::GetAccelerations()
{
	const double scaleFactor = 1.0;

	AxesReport data;
	UINT8 ACC_Data[6];
	
	UINT8 ctrl = 0;

	accelI2C_r->Read(OUT_X_L_A,1,ACC_Data+0);
	accelI2C_r->Read(OUT_X_H_A,1,ACC_Data+1);
	accelI2C_r->Read(OUT_Y_L_A,1,ACC_Data+2);
	accelI2C_r->Read(OUT_Y_H_A,1,ACC_Data+3);
	accelI2C_r->Read(OUT_Z_L_A,1,ACC_Data+4);
	accelI2C_r->Read(OUT_Z_H_A,1,ACC_Data+5);
	
	/*printf("I2C read at address: %x, ptr: %p\n",accelAddressR,accelI2C_r);
	printf("I2C write at address: %x, ptr: %p\n",accelAddressW,accelI2C_w);
	printf("OUT_X_L_A: %x\n",*(ACC_Data+0));
	printf("OUT_X_H_A: %x\n",*(ACC_Data+1));
	printf("OUT_Y_L_A: %x\n",*(ACC_Data+2));
	printf("OUT_Y_H_A: %x\n",*(ACC_Data+3));
	printf("OUT_Z_L_A: %x\n",*(ACC_Data+4));
	printf("OUT_Z_H_A: %x\n",*(ACC_Data+5));
	printf("Control Register: %x\n",ctrl);*/

	int rawX, rawY, rawZ;

	/*
	rawX = (int) (ACC_Data[0] << 8) + ACC_Data[1];
	rawY = (int) (ACC_Data[2] << 8) + ACC_Data[3];
	rawZ = (int) (ACC_Data[4] << 8) + ACC_Data[5];
	*/
	short* ConvertedData = (short*)ACC_Data;
	rawX = ConvertedData[0];
	rawY = ConvertedData[1];
	rawZ = ConvertedData[2];

	data.XAxis = (int) rawX;// * scaleFactor;
	data.YAxis = (int) rawY;// * scaleFactor;
	data.ZAxis = (int) rawZ;// * scaleFactor;

	return data;
}

LSM303_I2C::AxesReport LSM303_I2C::GetMagnetic()
{
	const double scaleFactor = 1.0;

	AxesReport data;
	unsigned char MagData[6];
	unsigned char tmp = 0;

	magI2C->Read(0x02,1,&tmp);

	for(int i = 0; i < 6; i++)
		magI2C->Read((int)OUT_X_H_M+i,1,MagData+i);

	int rawX, rawY, rawZ;

	rawX = (int) (MagData[0] << 8) + MagData[1];
	rawY = (int) (MagData[2] << 8) + MagData[3];
	rawZ = (int) (MagData[4] << 8) + MagData[5];

	data.XAxis = (int) rawX * scaleFactor;
	data.YAxis = (int) rawY * scaleFactor;
	data.ZAxis = (int) rawZ * scaleFactor;

	return data;
}

